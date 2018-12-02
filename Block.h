#pragma once
#include <ctime>
#include <string>
#include <vector>

using namespace std;
// todo: add templating to handle all kinds of data.
// TODO: remove dependence on string.
// VS doesn't highlight 'TODO'. Why the falooda? Going to check out C Lion or whatever it's called by Jetbrains.

struct HashlessBlock
{
	int index;
	time_t timestamp;
	size_t p_hash;
	string data;
};

size_t calculate_hash(HashlessBlock * block);

class Block
{
public:
	// utter disregard for data encapsulation
	int index;
	time_t timestamp;
	size_t p_hash;
	size_t hash;
	string data;
	static Block * latest_block;

	Block(int index, time_t timestamp, size_t p_hash, size_t hash, string data);
	~Block();
	static Block * get_latest_block();
};


Block * generate_next_block(string data);
Block * get_genesis_block();
bool check_validity_of_new_block(Block * previous_block, Block * new_block);
