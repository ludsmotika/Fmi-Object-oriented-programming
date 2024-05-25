#pragma once

class StringPool
{
public:

	StringPool();
	StringPool(const StringPool& other) = delete;
	StringPool(StringPool&& other) = delete;
	StringPool& operator = (const StringPool& other) = delete;
	StringPool& operator = (StringPool&& other) = delete;

	~StringPool();

	const char* getAllocatedString(const char* str);
	void releaseRecord(const char* str);

private:

	struct StringRecord
	{
		char* str = nullptr;
		unsigned referencesCount = 0;
	};

	int getIndexForRecord(const char* str) const;
	void resize();
	void allocateNewString(const char* str);
	void removeRecord(unsigned index);

	void free();

	StringRecord* records;
	size_t count;
	size_t capacity;

};