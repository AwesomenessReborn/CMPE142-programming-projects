#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOCKS 1000

typedef struct {
    int start;
    int end;
    char process[10];
    int is_free;
} MemoryBlock;

MemoryBlock memory[MAX_BLOCKS];
int block_count = 0;
int max_memory = 0;

void init_memory(int size) {
    max_memory = size;
    memory[0].start = 0;
    memory[0].end = size - 1;
    strcpy(memory[0].process, "");
    memory[0].is_free = 1;
    block_count = 1;
}

void print_status() {
    printf("\n=== Memory Status ===\n");
    for (int i = 0; i < block_count; i++) {
        printf("Addresses [%d:%d] ", memory[i].start, memory[i].end);
        if (memory[i].is_free) {
            printf("Unused\n");
        } else {
            printf("Process %s\n", memory[i].process);
        }
    }
    printf("====================\n\n");
}

int find_first_fit(int size) {
    for (int i = 0; i < block_count; i++) {
        if (memory[i].is_free && (memory[i].end - memory[i].start + 1) >= size) {
            return i;
        }
    }
    return -1;
}

int find_best_fit(int size) {
    int best_idx = -1;
    int best_size = max_memory + 1;
    
    for (int i = 0; i < block_count; i++) {
        if (memory[i].is_free) {
            int block_size = memory[i].end - memory[i].start + 1;
            if (block_size >= size && block_size < best_size) {
                best_size = block_size;
                best_idx = i;
            }
        }
    }
    return best_idx;
}

int find_worst_fit(int size) {
    int worst_idx = -1;
    int worst_size = -1;
    
    for (int i = 0; i < block_count; i++) {
        if (memory[i].is_free) {
            int block_size = memory[i].end - memory[i].start + 1;
            if (block_size >= size && block_size > worst_size) {
                worst_size = block_size;
                worst_idx = i;
            }
        }
    }
    return worst_idx;
}

void allocate_memory(char* process, int size, char strategy) {
    int idx = -1;
    
    if (strategy == 'F') {
        idx = find_first_fit(size);
    } else if (strategy == 'B') {
        idx = find_best_fit(size);
    } else if (strategy == 'W') {
        idx = find_worst_fit(size);
    } else {
        printf("Error: Invalid strategy '%c'. Use F, B, or W.\n", strategy);
        return;
    }
    
    if (idx == -1) {
        printf("Error: Not enough memory to allocate %d bytes for process %s\n", size, process);
        return;
    }
    
    int block_size = memory[idx].end - memory[idx].start + 1;
    
    if (block_size == size) {
        // Exact fit
        memory[idx].is_free = 0;
        strcpy(memory[idx].process, process);
    } else {
        // Split the block
        // Shift all blocks after idx to make room
        for (int i = block_count; i > idx; i--) {
            memory[i] = memory[i - 1];
        }
        
        // Allocated block
        memory[idx].end = memory[idx].start + size - 1;
        memory[idx].is_free = 0;
        strcpy(memory[idx].process, process);
        
        // Free block (remaining space)
        memory[idx + 1].start = memory[idx].end + 1;
        memory[idx + 1].is_free = 1;
        strcpy(memory[idx + 1].process, "");
        
        block_count++;
    }
    
    printf("Successfully allocated %d bytes to process %s\n", size, process);
}

void release_memory(char* process) {
    int found = 0;
    
    for (int i = 0; i < block_count; i++) {
        if (!memory[i].is_free && strcmp(memory[i].process, process) == 0) {
            memory[i].is_free = 1;
            strcpy(memory[i].process, "");
            found = 1;
        }
    }
    
    if (!found) {
        printf("Error: Process %s not found\n", process);
        return;
    }
    
    printf("Released memory for process %s\n", process);
    
    // Merge adjacent free blocks
    for (int i = 0; i < block_count - 1; i++) {
        if (memory[i].is_free && memory[i + 1].is_free) {
            memory[i].end = memory[i + 1].end;
            
            // Shift all blocks after i+1 down
            for (int j = i + 1; j < block_count - 1; j++) {
                memory[j] = memory[j + 1];
            }
            block_count--;
            i--; // Check again in case there are more adjacent free blocks
        }
    }
}

void compact_memory() {
    MemoryBlock temp[MAX_BLOCKS];
    int temp_count = 0;
    int current_start = 0;
    
    // Copy all allocated blocks to temp array
    for (int i = 0; i < block_count; i++) {
        if (!memory[i].is_free) {
            int size = memory[i].end - memory[i].start + 1;
            temp[temp_count].start = current_start;
            temp[temp_count].end = current_start + size - 1;
            temp[temp_count].is_free = 0;
            strcpy(temp[temp_count].process, memory[i].process);
            current_start += size;
            temp_count++;
        }
    }
    
    // Add remaining free space as one block
    if (current_start < max_memory) {
        temp[temp_count].start = current_start;
        temp[temp_count].end = max_memory - 1;
        temp[temp_count].is_free = 1;
        strcpy(temp[temp_count].process, "");
        temp_count++;
    }
    
    // Copy back to memory
    for (int i = 0; i < temp_count; i++) {
        memory[i] = temp[i];
    }
    block_count = temp_count;
    
    printf("Memory compacted successfully\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <memory_size>\n", argv[0]);
        printf("Example: %s 1048576\n", argv[0]);
        return 1;
    }
    
    int size = atoi(argv[1]);
    if (size <= 0) {
        printf("Error: Invalid memory size\n");
        return 1;
    }
    
    init_memory(size);
    printf("Memory initialized with %d bytes (0 to %d)\n\n", size, size - 1);
    
    char command[100];
    char process[10];
    int mem_size;
    char strategy;
    
    while (1) {
        printf("allocator> ");
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }
        
        // Remove newline
        command[strcspn(command, "\n")] = 0;
        
        if (strlen(command) == 0) {
            continue;
        }
        
        char cmd[10];
        sscanf(command, "%s", cmd);
        
        if (strcmp(cmd, "RQ") == 0) {
            if (sscanf(command, "%*s %s %d %c", process, &mem_size, &strategy) != 3) {
                printf("Error: RQ command requires process ID, size, and strategy (F/B/W)\n");
                printf("Usage: RQ <process> <size> <strategy>\n");
                continue;
            }
            allocate_memory(process, mem_size, strategy);
            
        } else if (strcmp(cmd, "RL") == 0) {
            if (sscanf(command, "%*s %s", process) != 1) {
                printf("Error: RL command requires process ID\n");
                printf("Usage: RL <process>\n");
                continue;
            }
            release_memory(process);
            
        } else if (strcmp(cmd, "C") == 0) {
            compact_memory();
            
        } else if (strcmp(cmd, "STAT") == 0) {
            print_status();
            
        } else if (strcmp(cmd, "X") == 0) {
            printf("Exiting...\n");
            break;
            
        } else {
            printf("Error: Unknown command '%s'\n", cmd);
            printf("Available commands: RQ, RL, C, STAT, X\n");
        }
    }
    
    return 0;
}