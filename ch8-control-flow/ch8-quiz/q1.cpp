#include <iostream>

namespace Ball {
// Gets tower height from user and returns it
	double get_tower_height() {
		std::cout << "Enter the height of the tower in meters: ";
		double tower_height{};
		std::cin >> tower_height;
		return tower_height;
	}

	// Returns the current ball height after "seconds" seconds
	constexpr double calculate_ball_height(double tower_height, int seconds) {
		constexpr double gravity { 9.8 };

		// Using formula: s = (u * t) + (a * t^2) / 2
		// here u (initial velocity) = 0, so (u * t) = 0
		const double fall_distance { gravity * (seconds * seconds) / 2.0 };
		const double ball_height { tower_height - fall_distance };

		// If the ball would be under the ground, place it on the ground
		if (ball_height < 0.0)
			return 0.0;

		return ball_height;
	}

	// Prints ball height above ground
	void print_ball_height(double ball_height, int seconds) {
		if (ball_height > 0.0)
			std::cout << "At " << seconds << " seconds, the ball is at height: " << ball_height << " meters\n";
		else
			std::cout << "At " << seconds << " seconds, the ball is on the ground.\n";
	}

	// Calculates the current ball height and then prints it
	// This is a helper function to make it easier to do this
	double calculate_and_print_ball_height(double tower_height, int seconds) {
		const double ball_height { calculate_ball_height(tower_height, seconds) };
		print_ball_height(ball_height, seconds);
		return ball_height;
	}
}

int main() {
	double tower_height{ Ball::get_tower_height() };
	int seconds {};

	while ( Ball::calculate_and_print_ball_height(tower_height, seconds) > 0) {
		seconds++;
	}

	return 0;
}