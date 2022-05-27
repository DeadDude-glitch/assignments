#pragma once
struct Node
{
	char label;
	int cost;

	Node() { label = '?'; cost = 0; }					// defined state but not initialized state
	bool isDefined() {
		if (label == '?' && cost == 0 && tolower(label - 97) < 0) return false;
		else return true;
	}
};

struct edge { int weight; char v1_label; char v2_label; };