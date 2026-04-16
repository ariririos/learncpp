int main() {
    /*
    instead of writing:
    ```
    try {
        open_file(filename);
        write_file(filename, data);
        close_file(filename);
    } catch (const FileException& exception) {
        std::cerr << "Failed to write to file: " << exception.what() << "\n"; 
    }
    ```
    we should move cleanup after the catch block:
    ```
    try {
        open_file(filename);
        write_file(filename, data);
    } catch (const FileException& exception) {
        std::cerr << "Failed to write to file: " << exception.what() << "\n"; 
    }
    close_file(filename);
    ```
    */

    /*
    when dealing with dynamic memory, if we declare the variable inside of the try block, we won't be able to delete it from outside after the catch block:
    ```
    try {
        auto* john { new Person { "john", 18, PERSON_MALE }};
        process_person(john);
        delete john;
    }
    catch (const PersonException& exception) {
        std::cerr << "Failed to process person: " << exception.what() << "\n";
    }
    // if we get here john was never deallocated
    ```
    we can instead move the variable declaration outside the try block then delete it after the catch:
    ```
    Person* john { nullptr };

    try {
        john = new Person("John", 18, PERSON_MALE);
        process_person(john);
    }
    catch (const PersonException& exception) {
        std::cerr << "Failed to process person: " << exception.what() << "\n";
    }
    
    delete john;
    ```
    but the best option is to stack allocate an object that implements RAII like std::unique_ptr, which ensures that the object will be cleaned up whenever it goes out of scope for any reason
    */

    // we shouldn't use exceptions in destructors at all, because if an exception is thrown out of a destructor during stack unwinding, then the compiler has two paths to follow: continue stack unwinding or handle the new exception
    // it will instead decide to terminate the program at that point, so the best course of action is to just log to a file

    // exceptions normally have a small performance cost during runtime, due to the additional checks being performed, but the main cost is when they are actually thrown and the stack must be unwound
    // but some architectures support zero-cost exceptions which have no runtime cost in the non-error case (but a larger penalty when exceptions do occur)

    // overall this means exceptions are most useful when all of the following are true:
    // - the error being handled is infrequent
    // - the error is serious and requires halting execution
    // - the error cannot be handled at the place where it occurs
    // - there isn't a good alternative way to return an error code to the caller (!)

    return 0;
}