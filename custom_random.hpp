// Simple rand algorithm in its own namespace to prevent clutter

namespace crand
{
	// max 32uint
	const unsigned int MAX_RAND = 4294967295;
	unsigned int current = 0;
	void srand(unsigned int seed)
	{
		current = seed;
	}
	unsigned int rand()
	{
		// We just multiply by Jenny's phone number, add our haxor skill, and then modulos by max rand.
		current = (current * 8675309 + 1337) % (MAX_RAND);
		return current;
	}
	unsigned int getSeed()
	{
		return current;
	}
}