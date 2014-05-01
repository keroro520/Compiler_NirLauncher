
typedef struct Memory {
	void * base;
	void * next;
	int rest;
} Memory;

Memory * mem ;

void memoryReply(Memory * mem)
{
	Memory * tmp = malloc(sizeof Memory);
	tmp->base = malloc(NMEMORYREPLY);
	tmp->rest = NMEMORYREPLY;
	tmp->next = NULL;
	mem->next = tmp;
}

void memoryInit()
{
	Memory * mem = malloc(sizeof Memory);
	Memory * old = mem;
	memoryReply(mem);
	mem = mem->next;
	free(old);
}
