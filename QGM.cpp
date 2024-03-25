#include <iostream>
#include <vector>
#include <cmath>
#include <random>

// Parameters for the QG model
double a = 0.1;
double b = 0.05;
double c = 0.01;
double sigma = 0.02;

// Time step and number of paths
double dt = 0.01;
int num_paths = 10000;

// Function to simulate a single path
std::vector<double> simulate_path(int num_steps, double r0, std::mt19937& gen) {
    std::vector<double> path(num_steps);
    path[0] = r0;

    std::normal_distribution<double> dist(0.0, std::sqrt(dt));

    for (int i = 1; i < num_steps; ++i) {
        double dW = dist(gen);
        path[i] = path[i-1] + a * (b - path[i-1]) * dt + sigma * (1 + c * path[i-1]) * dW;
    }

    return path;
}

int main() {
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Simulate paths
    std::vector<std::vector<double>> paths(num_paths);
    for (int i = 0; i < num_paths; ++i) {
        paths[i] = simulate_path(int(1/dt), 0.05, gen);
    }

    // Calculate bond prices (assuming zero-coupon bonds)
    std::vector<double> bond_prices(num_paths);
    for (int i = 0; i < num_paths; ++i) {
        double bond_price = 0.0;
        for (double r : paths[i]) {
            bond_price += std::exp(-r * dt);
        }
        bond_prices[i] = bond_price;
    }
  for (int i = 0; i < num_paths; ++i) {
      std::cout << "Bond price for path " << i+1 << ": " << bond_prices[i] << std::endl;
  }

    // Output the average bond price
    double avg_bond_price = 0.0;
    for (double p : bond_prices) {
        avg_bond_price += p;
    }
    avg_bond_price /= num_paths;

    std::cout << "Average bond price: " << avg_bond_price << std::endl;

    return 0;
}


