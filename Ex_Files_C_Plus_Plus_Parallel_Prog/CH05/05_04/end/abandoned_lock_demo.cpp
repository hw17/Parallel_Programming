/**
 * Two philosophers, thinking and eating sushi
 */
#include <thread>
#include <mutex>

int sushi_count = 5000;

void philosopher(std::mutex &chopsticks) {
    while (sushi_count > 0) {
        /* the scoped_lock will only hold onto is lock of the mutex
        for the scope in which the scoped locked object was created
        which is the while loop iteration */
        std::scoped_lock lock(chopsticks);
        if (sushi_count) {
            sushi_count--;
        }
        if (sushi_count == 10) {
            printf("This philosopher has had enough!\n");
            break;
            /*if something happens to make the loop exit prematurely,
            like at line 20, the scope locked will automatically release
            its lock on the mutex for another thread to take */
        }
    }
}

int main() {
    std::mutex chopsticks;
    std::thread barron(philosopher, std::ref(chopsticks));
    std::thread olivia(philosopher, std::ref(chopsticks));
    barron.join();
    olivia.join();
    printf("The philosophers are done eating.\n");
}