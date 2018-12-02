#include "Block.h"
#include <iostream>
using namespace std;

Block * Block::latest_block = NULL;

size_t calculate_hash(HashlessBlock & block)
{
	_Bitwise_hash <HashlessBlock> hash_fn;
	size_t hash = hash_fn(block);
	return hash;
}

Block::Block(int index, time_t timestamp, size_t p_hash, size_t hash, string data)
{
	Block::index = index;
	Block::timestamp = timestamp;
	Block::p_hash = p_hash;
	Block::data = data;
	Block::hash = hash;

	Block::latest_block = this;
}

Block::~Block()
{
}

Block * Block::get_latest_block()
{
	return latest_block;
}

Block * generate_next_block(string data)
{
	Block * p_block = Block::get_latest_block();
	int index = p_block->index + 1;
	time_t timestamp;
	time(&timestamp);
	size_t p_hash = p_block->hash;
	HashlessBlock new_block;
	new_block.data = data;
	new_block.p_hash = p_hash;
	new_block.timestamp = timestamp;
	new_block.index = index;

	size_t hash = calculate_hash(new_block);

	Block * block = new Block(index, timestamp, p_hash, hash, data);
	return block;
}

Block * get_genesis_block()
{
	HashlessBlock block_data;
	block_data.data = "genesis";
	block_data.index = 0;
	block_data.p_hash = 0;
	block_data.timestamp = time(0);
	
	size_t hash = calculate_hash(block_data);
	Block * genesis = new Block(block_data.index, block_data.timestamp, block_data.p_hash, hash, 
		block_data.data);
	return genesis;
}

bool check_validity_of_new_block(Block * previous_block, Block * new_block)
{
	if (new_block->index != previous_block->index + 1)
	{
		cerr << __TIMESTAMP__ << ": New block's index invalid.\n";
		return false;
	}
	if (new_block->p_hash != previous_block->hash)
	{
		cerr << __TIMESTAMP__ << ": Previous block's hash reported by new block doesn't match with previous block's actual hash.\n";
		return false;
	}
	HashlessBlock new_block_data = { new_block->index, new_block->timestamp, new_block->p_hash, new_block->data };
	size_t new_hash = calculate_hash(new_block_data);
	if (new_hash != new_block->hash)
	{
		cerr << __TIMESTAMP__ << ": New block's hash is invalid.\n";
		return false;
	}
	return true;
}