#include <iostream>

namespace Duplication {
    class PoweredDevice {
    public:
        PoweredDevice(int power) {
            std::cout << "PoweredDevice: " << power << "\n";
        }
    };

    class Scanner : public PoweredDevice {
    public:
        Scanner(int scanner, int power) : PoweredDevice { power } {
            std::cout << "Scanner: " << scanner << "\n";
        }
    };

    class Printer : public PoweredDevice {
    public:
        Printer(int printer, int power) : PoweredDevice { power } {
            std::cout << "Printer: " << printer << "\n";
        }
    };

    class Copier : public Scanner, public Printer {
    public:
        Copier(int scanner, int printer, int power)
            : Scanner { scanner, power }, Printer { printer, power } {}
    };
} // namespace Duplication

namespace Example {
    class PoweredDevice {};
    class Scanner : virtual public PoweredDevice {};
    class Printer : virtual public PoweredDevice {};
    class Copier : public Scanner, public Printer {};
} // namespace Example

namespace VirtualBaseClasses {
    class PoweredDevice {
    public:
        PoweredDevice(int power) {
            std::cout << "PoweredDevice: " << power << "\n";
        }
    };

    class Scanner : virtual public PoweredDevice {
    public:
        Scanner(int scanner, int power)
            : PoweredDevice {
                  power
              } { // the `PoweredDevice { power }` part is required to initialize Scanner objects but actually gets ignored in this case
            std::cout << "Scanner: " << scanner << "\n";
        }
    };

    class Printer : virtual public PoweredDevice {
    public:
        Printer(int printer, int power)
            : PoweredDevice {
                  power
              } { // the `PoweredDevice { power }` part is required to initialize Printer objects but actually gets ignored in this case
            std::cout << "Printer: " << printer << "\n";
        }
    };

    class Copier : public Scanner, public Printer {
    public:
        Copier(int scanner, int printer, int power)
            : PoweredDevice { power }, Scanner { scanner, power },
              Printer { printer, power } {}
    };
}; // namespace VirtualBaseClasses

int main() {
    // recalling the diamond problem from 24.9, we might expect that creating a Copier will result in one copy of the ultimate base class PoweredDevice, but it will actually result in two:
    std::cout << "Duplication::Copier: \n";
    Duplication::Copier copier {
        1, 2, 3
    }; // prints PoweredDevice twice, Scanner and Printer once each

    // we can instead use PoweredDevice as a "virtual base class" by using `virtual` in the inheritance declaration, which creates a single base object shared by all objects in the inheritance tree, constructed once
    // (see Example namespace)

    // when we have actual constructors for these classes, it turns out that neither Scanner nor Printer are responsible for constructing PoweredDevice, but actually Copier
    // this is the one time when Copier is allowed to call a non-immediate-parent constructor directly
    std::cout << "\n\nVirtualBaseClasses::Copier: \n";
    VirtualBaseClasses::Copier copier2 {
        1, 2, 3
    }; // PoweredDevice, Scanner, and Printer each get constructed once

    // for the constructor of the most derived class, virtual base classes are always created before non-virtual base classes (even if declared otherwise, causing -Wreorder), so that all bases are created before their derived classes
    // Scanner and Printer still have calls to the PoweredDevice constructor in case they were to be initialized on their own rather than through Copier
    // if a class inherits from one or more classes that have virtual parents, the most derived class is responsible for constructing the virtual base class, even in a single inheritance case (e.g. if Copier singly inherits from Printer, which virtually inherits from PoweredDevice, Copier is still responsible for creating PoweredDevice)
    // all classes inheriting from a virtual base class will have a virtual table even if they wouldn't have otherwise, and will thus be larger by a pointer; e.g. Scanner and Printer derive virtually from PoweredDevice, and Copier will only be one PoweredDevice subobject, but Scanner and Printer still need to know where to find that single PoweredDevice subobject through virtual table magic (storing the offset from each subclass to the subobject)

    return 0;
}