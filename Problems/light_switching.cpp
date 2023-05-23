// Time complexity: O(n*log(n)). Space complexity: O(n).

#include <algorithm>
#include <iostream>
#include <vector>

// This function takes a vector of pairs representing the start and end times
// of people entering and leaving a room. It returns the number of times the
// light in the room was turned on.
int times(const std::vector<std::pair<int, int>>& persons) {
    // Create a vector to store events.
    std::vector<std::pair<int, int>> events;

    // Reserve space for the known number of people. 
    events.reserve(persons.size());

    // For each person, add two events to the vector: one for entering the room
    // and one for leaving the room. The second element of each pair is 1 for
    // entering and -1 for leaving.
    for (const auto& [entryTime, exitTime] : persons) {
        events.emplace_back(entryTime, 1);
        events.emplace_back(exitTime, -1);
    }
    // Sort the events in ascending order by time.
    std::sort(events.begin(), events.end());

    // This variable will keep track of the number of times the light was turned on.
    int lightOnCount = 0;

    // This variable will keep track of the number of persons currently in the room.
    int personCount = 0;

    // Process each event in order.
    for (const auto& [eventTime, eventType] : events) {
        if (eventType == 1) {
            // If this is an entering event and there is no one currently in
            // the room, increment count and turn on the light.
            if (personCount == 0) {
                ++lightOnCount;
            }
            // Increment light to indicate that there is one more person in
            // the room.
            ++personCount;
        } else {
            // If this is a leaving event, decrement light to indicate that
            // there is one less person in the room.
            --personCount;
        }
    }
    // Return the final count.
    return lightOnCount;
}

int main() {
    std::cout << times({{1, 5}, {2, 6}, {3, 7}}) << std::endl;                  // 1
    std::cout << times({{11, 15}, {1, 10}, {2, 8}, {5, 12}}) << std::endl;      // 1
    std::cout << times({{5, 7}, {6, 8}, {9, 10}, {1, 3}, {2, 4}}) << std::endl; // 3
    std::cout << times({{1, 2}, {2, 3}, {3, 4}}) << std::endl;                  // 3
    std::cout << times({{}}) << std::endl;                                      // 0
}
