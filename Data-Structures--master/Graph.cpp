#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <sstream>
#include <queue>


using namespace std;

// fwd declarations
string make_dot(Graph* g);
string what(int& v);

Graph::Graph() {
  // DONE FOR YOU
  directed = false; // graphs are undirected by default
}

Graph::~Graph() {
  // "DONE" FOR YOU
  // no implementation needed
}

vector<shared_ptr<Node>> Graph::getNodes() {
  // DONE FOR YOU
  return nodes;
}

vector<shared_ptr<Edge>> Graph::getEdges() {
  // DONE FOR YOU
  return edges;
}

int Graph::getClock() {
  // DONE FOR YOU
  return clock;
}

void Graph::addNode(shared_ptr<Node> n) {
  // DONE FOR YOU
  nodes.push_back(n);
}

void Graph::addEdge(shared_ptr<Edge> e) {
  // DONE FOR YOU
  edges.push_back(e);
}
 
void Graph::removeNode(shared_ptr<Node> n) {
  // DONE FOR YOU
  for (vector<shared_ptr<Node>>::iterator it = nodes.begin(); it != nodes.end(); it++) {
    if (n == *it) {
      nodes.erase(it);
      break;
    }
  }
}
 
void Graph::removeEdge(shared_ptr<Edge> e) {
  // DONE FOR YOU
  for (vector<shared_ptr<Edge>>::iterator it = edges.begin();
       it != edges.end(); 
       it++) {
    if (e == *it) {
      edges.erase(it);
      break;
    }
  }
}

void Graph::setDirected(bool val) {
  // DONE FOR YOU
  directed = val;
}

bool Graph::isDirected() {
  // DONE FOR YOU
  return directed;
}

set<shared_ptr<Edge>> Graph::getAdjacentEdges(shared_ptr<Node> n) {
  // DONE FOR YOU
  set<shared_ptr<Edge>> ret;
  for (vector<shared_ptr<Edge>>::iterator it = edges.begin(); it != edges.end(); it++) {
    shared_ptr<Edge> edge = *it;
    if (edge->getStart() == n) {
      ret.insert(edge);
    }
    if (!directed && (edge->getEnd() == n)) {
      ret.insert(edge);
    }
  }
  return ret;
}

void Graph::clear() {
  // TODO
  for (unsigned int i = 0; i < this->nodes.size(); i++) {
    this->nodes[i]->clear();
  }
  for (unsigned int i = 0; i < this->edges.size(); i++) {
    this->edges[i]->setType(UNDISCOVERED_EDGE);
  }
  this->clock = 0;
}

void Graph::tick(string message) {
  // DONE FOR YOU
  //
  // optional debugging function, disabled with if(false) to prevent
  // unused var warning. Change this however you want.
  //
  // recommended use: call it just after incrementing the clock.
  if (false) {
    cout << "// " << message << endl << make_dot(this) << endl;
  }
}

void Graph::dfs(shared_ptr<Node> start) {
  // TODO
  start->setColor(GRAY, this->clock);
  this->clock +=  1;
  set<shared_ptr<Edge>> related_edges = this->getAdjacentEdges(start);
  for(auto related_edge : related_edges) {
    shared_ptr<Node> edge_start = related_edge->getStart();
    shared_ptr<Node> edge_end = related_edge->getEnd();
    shared_ptr<Node> related_node;
    if (edge_start == start) {
      related_node = edge_end;
    } else {
      related_node = edge_start;
    }
    int related_color;
    int related_disco_time;
    int related_finish_time;
    int related_bfs_rank;
    related_node->getDiscoveryInformation(related_color, related_disco_time, related_finish_time, related_bfs_rank);

    if (related_color == WHITE) {
      edge_end->setPredecessor(edge_start);
      related_edge->setType(TREE_EDGE);
      this->dfs(related_node);
    } else if (related_color == GRAY) {
      related_edge->setType(BACK_EDGE);
    } else {
      if (edge_end->isAncestor(edge_start)) {
        related_edge->setType(FORWARD_EDGE);
      } else {
        related_edge->setType(CROSS_EDGE);
      }
    }
  }
  start->setColor(BLACK, this->clock);
  this->clock += 1;
}


void Graph::bfs(shared_ptr<Node> start) {
  // TODO
  queue<shared_ptr<Node>> search_queue;
  int rank = 0;

  search_queue.push(start);
  start->setColor(GRAY, this->clock);
  start->setRank(rank);
  this->clock += 1;

  while (!search_queue.empty()) {
    shared_ptr<Node> node = search_queue.front();
    search_queue.pop();
    node->setColor(BLACK, this->clock);
    this->clock += 1;
    int color;
    int disco_time;
    int finish_time;
    int bfs_rank;
    node->getDiscoveryInformation(color, disco_time, finish_time, bfs_rank);
    set<shared_ptr<Edge>> related_edges = this->getAdjacentEdges(node);
    for(auto related_edge : related_edges) {
      shared_ptr<Node> other_node = related_edge->getEnd();
      int related_color;
      int related_disco_time;
      int related_finish_time;
      int related_bfs_rank;
      other_node->getDiscoveryInformation(related_color, related_disco_time, related_finish_time, related_bfs_rank);
      if (related_color == WHITE) {
        other_node->setColor(GRAY, this->clock);
        this->clock += 1;
        search_queue.push(other_node);
      }
      if (related_bfs_rank == -1 || related_bfs_rank > bfs_rank + 1) {
        cout << other_node->getData() << " RANK IS NOW " << (bfs_rank + 1) << endl;
        other_node->setRank(bfs_rank + 1);
      }
    }
  }
}

void Graph::bfs(shared_ptr<Node> start, shared_ptr<Node> finish) {
  // TODO
  bool stop = false;
  queue<shared_ptr<Node>> search_queue;
  int rank = 0;

  search_queue.push(start);
  start->setColor(GRAY, this->clock);
  start->setRank(rank);
  this->clock += 1;

  while (!search_queue.empty()) {
    shared_ptr<Node> node = search_queue.front();
    search_queue.pop();
    node->setColor(BLACK, this->clock);
    this->clock += 1;
    int color;
    int disco_time;
    int finish_time;
    int bfs_rank;
    node->getDiscoveryInformation(color, disco_time, finish_time, bfs_rank);
    set<shared_ptr<Edge>> related_edges = this->getAdjacentEdges(node);
    for(auto related_edge : related_edges) {
      shared_ptr<Node> another_node = related_edge->getEnd();
      int related_color;
      int related_disco_time;
      int related_finish_time;
      int related_bfs_rank;
      another_node->getDiscoveryInformation(related_color, related_disco_time, related_finish_time, related_bfs_rank);
      if (!stop && related_color == WHITE) {
        another_node->setColor(GRAY, this->clock);
        this->clock += 1;
        search_queue.push(another_node);
      }
      if (related_bfs_rank == -1 || related_bfs_rank > bfs_rank + 1) {
        cout << another_node->getData() << " RANK IS NOW " << (bfs_rank + 1) << endl;
        if (this->isDirected()) {
          another_node->setRank(bfs_rank + 1);
        } else {
          another_node->setRank(1);
        }
      }
      if (another_node->getData() == finish->getData()) {
        stop = true;
      }
    }
  }
}

// overloading operator << lets you put a Graph object into an output
// stream.
ostream &operator << (ostream& out, Graph graph) {
  // DONE FOR YOU
  out << graph.nodes.size() << " Nodes:" << endl;
  out << "[";
  for (vector<shared_ptr<Node>>::iterator it = graph.nodes.begin(); it != graph.nodes.end(); it++) {
    shared_ptr<Node> n = *it;
    out << *n << ", ";
  }
  out << "]" << endl;
  out << graph.edges.size() << " Edges:" << endl;
  out << "[";
  for (vector<shared_ptr<Edge>>::iterator it = graph.edges.begin(); it != graph.edges.end(); it++) {
    shared_ptr<Edge> e = *it;
    out << *e << ", ";
  }
  out << "]";
  return out;
}

// what is a helper function that turns a constant (e.g. WHITE or
// FORWARD_EDGE) into a string for debugging goodness. 
string what(int& v) {
  // DONE FOR YOU
  string ret = "Unknown";
  if (v == WHITE) {
    ret = "white";
  } else if (v == GRAY) {
    ret = "gray";
  } else if (v == BLACK) {
    ret = "black";
  } else if (v == UNDISCOVERED_EDGE) {
    ret = "undiscovered";
  } else if (v == TREE_EDGE) {
    ret = "tree";
  } else if (v == BACK_EDGE) {
    ret = "back";
  } else if (v == FORWARD_EDGE) {
    ret = "forward";
  } else if (v == CROSS_EDGE) {
    ret = "cross";
  }
  return ret;
}

// make_dot generates a dotfile string for viewing your graph. Have
// tick() print out the results of this function, and then use
// http://www.webgraphviz.com/ (or get a copy of GraphViz) to view the
// result. If you're stuck, this can help you get un-stuck.
string make_dot(Graph* g) {
  // DONE FOR YOU
  stringstream ss;
  vector<shared_ptr<Node>> nodes = g->getNodes();
  vector<shared_ptr<Edge>> edges = g->getEdges();
  string gt = "graph";
  string con = "--";
  if (g->isDirected()) {
    con = "->";
    gt = "digraph";
  }
  ss << gt << " homework {" << endl;
  int c, dt, ft, r;
  string textColor = "black";
  for (auto it=nodes.begin(); it != nodes.end(); ++it) {
    shared_ptr<Node> n = *it;
    n->getDiscoveryInformation(c, dt, ft, r);
    if (c == BLACK) {
      textColor = "white";
    } else {
      textColor = "black";
    }
    ss << "  " << n->getData() << " [ style=\"filled\" fontcolor=\"" << textColor << "\" fillcolor=\"" << what(c) << "\"" << " ]" << endl;
  }
  
  string edgeColor = "black";
  for (auto it=edges.begin(); it != edges.end(); ++it) {
    shared_ptr<Edge> e = *it;
    if (e->getType() == TREE_EDGE) {
      edgeColor = "black";
    } else if (e->getType() == FORWARD_EDGE) {
      edgeColor = "purple";
    } else if (e->getType() == BACK_EDGE) {
      edgeColor = "blue";
    } else if (e->getType() == CROSS_EDGE) {
      edgeColor = "green";
    } else {
      edgeColor = "gray";
    }
    ss << "  " << e->getStart()->getData() << con << e->getEnd()->getData() << " [color=\"" << edgeColor << "\"]" << endl;
  }
  ss << "}" << endl;
  return ss.str();
}