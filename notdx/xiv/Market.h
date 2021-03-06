#pragma once

template <typename T>
struct iGenericT {
	int Count; 
	T Items[100];
};

struct iSearchResult {
	int Price, Qty, HQ, 
		City, Materia, OnMann;
};

typedef struct iGenericT
<iSearchResult> IntResults;

template <typename T>
struct aGenericT {
	char *_NIL, *Hits;
	T Items[100];
};

struct aSearchResult {
	char *Price, *Total, 
		*Qty, *City, *Retainer;
};

typedef struct aGenericT
	<aSearchResult> StrResults;

struct j_search_t {
	int _nil, iCity;
	char *Price, *Total, 
		*Qty, *Retainer, *City;
	BYTE iMateria, isHQ;
	char _pad[6];
};

class MarketWindow {
public:
	void* _pad1[44]; // 0
	struct {
		int type, _pad_0; 
		int value, _pad_1;
	} *Properties;
	void* pad[31]; // weh
	void* n_608;
	void* n_616;
	void* n_624;
	void* n_632;
	struct j_search_t* Items; // 640
	void* n_648;
	void* n_656;
};