import matplotlib.pyplot as plt

# Read the file and extract the vectors
def read_vectors(file_path):
    vectors = []
    with open(file_path, 'r') as file:
        current_vector = []
        for line in file:
            line = line.strip()
            if line.startswith("Vector"):
                # Save the previous vector if it exists
                if current_vector:
                    vectors.append(current_vector)
                current_vector = []
            else:
                # Split line into numbers and convert them to integers
                current_vector.extend(map(int, line.split()))
        # Add the last vector
        if current_vector:
            vectors.append(current_vector)
    return vectors

# Plot the percentage distribution of X wins, Y wins, and Draws over time
def plot_outcomes_percentage_over_time(vectors):
    if len(vectors) != 3:
        print("Error: Expected 3 vectors for X wins, Y wins, and Draws.")
        return

    vector_x_wins = vectors[0]
    vector_y_wins = vectors[1]
    vector_draws = vectors[2]

    total_games = len(vector_x_wins)
    percentages_x_win = []
    percentages_y_win = []
    percentages_draw = []

    for i in range(1, total_games + 1):
        count_x_win = sum(vector_x_wins[:i])
        count_y_win = sum(vector_y_wins[:i])
        count_draw = sum(vector_draws[:i])

        all = count_x_win + count_y_win + count_draw
        if all == 0:
            all = 1
        # Calculate percentages
        percentages_x_win.append((count_x_win / all) * 100)
        percentages_y_win.append((count_y_win / all) * 100)
        percentages_draw.append((count_draw / all) * 100)

    # Plot the percentage distribution over time
    plt.figure(figsize=(10, 6))
    plt.plot(percentages_x_win, label='X Win (%)', color='red')
    plt.plot(percentages_y_win, label='Y Win (%)', color='blue')
    plt.plot(percentages_draw, label='Draw (%)', color='gray')
    plt.xlabel('Time Step')
    plt.ylabel('Percentage (%)')
    plt.title('Outcome Percentage Distribution Over Time')
    plt.legend()
    plt.grid(True)
    plt.savefig('outcomes_percentage_over_time_plot.png')  # Save the plot to a file
    print(f'Plot saved to outcomes_percentage_over_time_plot.png')

# Main function
if __name__ == "__main__":
    file_path = 'cmake-build-debug/vectors_data_10.txt'
    vectors = read_vectors(file_path)
    plot_outcomes_percentage_over_time(vectors)