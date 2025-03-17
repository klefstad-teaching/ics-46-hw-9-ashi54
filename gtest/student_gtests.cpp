#include <gtest/gtest.h>
#include "dijkstras.h"
#include "ladder.h"

Test(LadderTest, GenerateWordLadder_AshiToAdi) {
  set<string> word_list = {"ashi", "adi", "asid", "ashid", "ashiid"};

  vector<string> expected = {"ashi", "adi"};
  EXPECT_EQ(generate_word_ladder("ashi", "adi", word_list), expected);

}

TEST(LadderTest, GenerateWordLadder_AshidToAdi) {
    set<string> word_list = {"ashi", "adi", "ashid", "asid", "asid"};

    vector<string> expected = {"ashid", "asid", "adi"};
    EXPECT_EQ(generate_word_ladder("ashid", "adi", word_list), expected);
}

TEST(LadderTest, GenerateWordLadder_MomToMother) {
    set<string> word_list = {"mom", "moth", "mother", "mot"};

    vector<string> expected = {"mom", "mot", "moth", "mother"};
    EXPECT_EQ(generate_word_ladder("mom", "mother", word_list), expected);
}


TEST(DijkstraTest, ShortestPath_AshiGraph) {
    Graph graph;
    file_to_graph("small.txt", graph);

    vector<int> previous(graph.numVertices);
    vector<int> distances = dijkstra_shortest_path(graph, 0, previous);

    vector<int> expected = {0, 7, 15, 5, 14, 11, 12};  // Example expected path
    EXPECT_EQ(extract_shortest_path(distances, previous, 12), expected);
}


TEST(DijkstraTest, ShortestPath_NoPath) {
    Graph graph;
    file_to_graph("small.txt", graph);

    vector<int> previous(graph.numVertices);
    vector<int> distances = dijkstra_shortest_path(graph, 0, previous);

    EXPECT_EQ(extract_shortest_path(distances, previous, 99), vector<int>{});
}


TEST(DijkstraTest, PrintPath_Valid) {
    vector<int> path = {0, 7, 15, 5, 14, 11, 12};
    int cost = 8;

    testing::internal::CaptureStdout();
    print_path(path, cost);
    string output = testing::internal::GetCapturedStdout();
    
    EXPECT_EQ(output, "0 7 15 5 14 11 12 \nTotal cost is 8\n");
}


TEST(DijkstraTest, PrintPath_NoPath) {
    vector<int> empty_path;
    int cost = INF;

    testing::internal::CaptureStdout();
    print_path(empty_path, cost);
    string output = testing::internal::GetCapturedStdout();
    
    EXPECT_EQ(output, "No path found.\n");
}
