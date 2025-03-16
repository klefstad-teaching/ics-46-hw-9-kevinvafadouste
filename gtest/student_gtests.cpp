#include <gtest/gtest.h>
#include "dijkstras.h"
#include "ladder.h"
#include <set>
#include <vector>

using namespace std;

TEST(IsAdjacentTest, OneLetterDifference) {
    EXPECT_TRUE(is_adjacent("Lakers", "Bakers"));
}

TEST(IsAdjacentTest, OneLetterAdded) {
    EXPECT_TRUE(is_adjacent("Heat", "Heats"));
}

TEST(IsAdjacentTest, OneLetterRemoved) {
    EXPECT_TRUE(is_adjacent("Knicks", "Nick"));
}

TEST(GenerateWordLadderTest, BasicCase) {
    set<string> word_list = {"Lakers", "Bakers", "Rakers", "Rockets", "Nuggets"};
    vector<string> result = generate_word_ladder("Lakers", "Nuggets", word_list);
    EXPECT_EQ(result.size(), 4);
}

TEST(GenerateWordLadderTest, NoPathExists) {
    set<string> word_list = {"Lakers", "Nuggets"};
    vector<string> result = generate_word_ladder("Lakers", "Nuggets", word_list);
    EXPECT_TRUE(result.empty());
}

TEST(GenerateWordLadderTest, StartEqualsEnd) {
    set<string> word_list = {"Lakers", "Nuggets"};
    vector<string> result = generate_word_ladder("Lakers", "Lakers", word_list);
    EXPECT_TRUE(result.empty());
}

TEST(DijkstraTest, SingleEdgeGraph) {
    Graph G;
    G.numVertices = 2;
    G.resize(2);
    G[0].push_back(Edge(0, 1, 10));
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    EXPECT_EQ(distances[1], 10);
}

TEST(DijkstraTest, NoPathExists) {
    Graph G;
    G.numVertices = 3;
    G.resize(3);
    G[0].push_back(Edge(0, 1, 10));
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    EXPECT_EQ(distances[2], INF);
}

TEST(DijkstraTest, MultiplePaths) {
    Graph G;
    G.numVertices = 3;
    G.resize(3);
    G[0].push_back(Edge(0, 1, 10));
    G[0].push_back(Edge(0, 2, 5));
    G[2].push_back(Edge(2, 1, 2));
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    EXPECT_EQ(distances[1], 7);
}

