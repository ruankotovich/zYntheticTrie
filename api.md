# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`define `[`STORE`](#occurrence_8hpp_1ac677e3bf428ab129e0cc9153ad7f23c7)            | 
`define `[`CATEGORY`](#occurrence_8hpp_1a60d401f420413a119c88879ab1a4ab58)            | 
`define `[`BOTH`](#occurrence_8hpp_1a85ddca800985505ab1036cf0d1be748b)            | 
`public int `[`main`](#main_8cpp_1a0ddf1224851353fc92bfbff6f499fa97)`(int argc,char * argv)`            | 
`namespace `[`trie`](#namespacetrie) | 
`namespace `[`UData`](#namespaceUData) | 

## Members

#### `define `[`STORE`](#occurrence_8hpp_1ac677e3bf428ab129e0cc9153ad7f23c7) 

#### `define `[`CATEGORY`](#occurrence_8hpp_1a60d401f420413a119c88879ab1a4ab58) 

#### `define `[`BOTH`](#occurrence_8hpp_1a85ddca800985505ab1036cf0d1be748b) 

#### `public int `[`main`](#main_8cpp_1a0ddf1224851353fc92bfbff6f499fa97)`(int argc,char * argv)` 

# namespace `trie` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`trie::Engine`](#classtrie_1_1Engine) | 
`class `[`trie::Trie_t`](#classtrie_1_1Trie__t) | 
`class `[`trie::TrieNode_t`](#classtrie_1_1TrieNode__t) | 
`struct `[`trie::ActiveNode_t`](#structtrie_1_1ActiveNode__t) | 
`struct `[`trie::ActiveNodeComparator_t`](#structtrie_1_1ActiveNodeComparator__t) | 
`struct `[`trie::Occurrence_t`](#structtrie_1_1Occurrence__t) | 
`struct `[`trie::OccurrencePriorityComparator_t`](#structtrie_1_1OccurrencePriorityComparator__t) | 

# class `trie::Engine` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`Engine`](#classtrie_1_1Engine_1afb4a4e31f62f65229815fdecc7521711)`()` | 
`public  `[`~Engine`](#classtrie_1_1Engine_1aa25e2d6b8ccedc0440a8d3665282c0c7)`()` | 
`public std::string `[`searchForStore`](#classtrie_1_1Engine_1a0e1c51d772e040566b51e3ccba1c53e6)`(std::string query,int n_return)` | 
`public std::string `[`searchForStoreByCategory`](#classtrie_1_1Engine_1a83f460566c115b2aae74699526ed9cd6)`(std::string query,int n_return)` | 
`public std::string `[`search`](#classtrie_1_1Engine_1a7fbb5cbd7c4daae4b161c0439ee99fba)`(std::string query,int n_return)` | 
`public std::string `[`insertStore`](#classtrie_1_1Engine_1ac773b9d51a1b06e2016b4f4456ee0e52)`(unsigned int id,const std::string & name,const std::string & lat,const std::string & lng,const std::string & max_radius)` | 
`public std::string `[`insertCategory`](#classtrie_1_1Engine_1ab6987ce7d0fa3228190beb8b558504f0)`(unsigned int id,const std::string & name)` | 
`public std::string `[`updateStore`](#classtrie_1_1Engine_1a000a6e6dd3069574aab9a016fc56ba92)`(unsigned int id,const std::string & name,const std::string & lat,const std::string & lng,const std::string & max_radius)` | 
`public std::string `[`updateCategory`](#classtrie_1_1Engine_1ad0ee77668dd0285c9bf1b7ca6e0b9b9b)`(unsigned int id,const std::string & name)` | 
`public std::string `[`newRelationStoreCategory`](#classtrie_1_1Engine_1a9c8e41ea6c5639d6ff73e14972c64cb4)`(unsigned int id_store,unsigned int id_category)` | 
`public std::string `[`removeRelationStoreCategory`](#classtrie_1_1Engine_1af47363f680d487b72d239871e7742a8c)`(unsigned int id_store,unsigned int id_category)` | 
`public std::string `[`removeStore`](#classtrie_1_1Engine_1a3bac8e9972e737b19f826a761c45a41e)`(unsigned int id)` | 
`public std::string `[`removeCategory`](#classtrie_1_1Engine_1ab80bf04481a30ecc66546f824033a527)`(unsigned int id)` | 
`public std::string `[`getStoresByCategory`](#classtrie_1_1Engine_1afccc4ed803c61dd37297f6b44d678ecd)`(unsigned int id)` | 
`public std::string `[`getCategoriesByStore`](#classtrie_1_1Engine_1ab6ea338881874bdcdc77b371c64b7de8)`(unsigned int id)` | 
`public void `[`limitErrors`](#classtrie_1_1Engine_1a87192a75cc118ce3ad10bc7a01f73fd8)`(int)` | 
`public void `[`printTrieInfos`](#classtrie_1_1Engine_1a88210c278b0ba0efea2c2d0bab5ff064)`()` | 
`public void `[`init`](#classtrie_1_1Engine_1ada5ea073d36139a43280c2abcd1a639d)`()` | 

## Members

#### `public  `[`Engine`](#classtrie_1_1Engine_1afb4a4e31f62f65229815fdecc7521711)`()` 

#### `public  `[`~Engine`](#classtrie_1_1Engine_1aa25e2d6b8ccedc0440a8d3665282c0c7)`()` 

#### `public std::string `[`searchForStore`](#classtrie_1_1Engine_1a0e1c51d772e040566b51e3ccba1c53e6)`(std::string query,int n_return)` 

#### `public std::string `[`searchForStoreByCategory`](#classtrie_1_1Engine_1a83f460566c115b2aae74699526ed9cd6)`(std::string query,int n_return)` 

#### `public std::string `[`search`](#classtrie_1_1Engine_1a7fbb5cbd7c4daae4b161c0439ee99fba)`(std::string query,int n_return)` 

#### `public std::string `[`insertStore`](#classtrie_1_1Engine_1ac773b9d51a1b06e2016b4f4456ee0e52)`(unsigned int id,const std::string & name,const std::string & lat,const std::string & lng,const std::string & max_radius)` 

#### `public std::string `[`insertCategory`](#classtrie_1_1Engine_1ab6987ce7d0fa3228190beb8b558504f0)`(unsigned int id,const std::string & name)` 

#### `public std::string `[`updateStore`](#classtrie_1_1Engine_1a000a6e6dd3069574aab9a016fc56ba92)`(unsigned int id,const std::string & name,const std::string & lat,const std::string & lng,const std::string & max_radius)` 

#### `public std::string `[`updateCategory`](#classtrie_1_1Engine_1ad0ee77668dd0285c9bf1b7ca6e0b9b9b)`(unsigned int id,const std::string & name)` 

#### `public std::string `[`newRelationStoreCategory`](#classtrie_1_1Engine_1a9c8e41ea6c5639d6ff73e14972c64cb4)`(unsigned int id_store,unsigned int id_category)` 

#### `public std::string `[`removeRelationStoreCategory`](#classtrie_1_1Engine_1af47363f680d487b72d239871e7742a8c)`(unsigned int id_store,unsigned int id_category)` 

#### `public std::string `[`removeStore`](#classtrie_1_1Engine_1a3bac8e9972e737b19f826a761c45a41e)`(unsigned int id)` 

#### `public std::string `[`removeCategory`](#classtrie_1_1Engine_1ab80bf04481a30ecc66546f824033a527)`(unsigned int id)` 

#### `public std::string `[`getStoresByCategory`](#classtrie_1_1Engine_1afccc4ed803c61dd37297f6b44d678ecd)`(unsigned int id)` 

#### `public std::string `[`getCategoriesByStore`](#classtrie_1_1Engine_1ab6ea338881874bdcdc77b371c64b7de8)`(unsigned int id)` 

#### `public void `[`limitErrors`](#classtrie_1_1Engine_1a87192a75cc118ce3ad10bc7a01f73fd8)`(int)` 

#### `public void `[`printTrieInfos`](#classtrie_1_1Engine_1a88210c278b0ba0efea2c2d0bab5ff064)`()` 

#### `public void `[`init`](#classtrie_1_1Engine_1ada5ea073d36139a43280c2abcd1a639d)`()` 

# class `trie::Trie_t` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`Trie_t`](#classtrie_1_1Trie__t_1a5de6b677c32073f299be3c59cb722981)`()` | 
`public void `[`encodeCharacters`](#classtrie_1_1Trie__t_1acc0545c3bcba9b6cf045450a3a154411)`(const std::string &)` | 
`public void `[`addStopWords`](#classtrie_1_1Trie__t_1a804d74ea84fa95fefe9f3516831f40e7)`(const std::string &)` | 
`public bool `[`isStopWord`](#classtrie_1_1Trie__t_1abcc65ebc46c344395041af08568f418a)`(std::string)` | 
`public void `[`printTrie`](#classtrie_1_1Trie__t_1a24b16e350ae27a7e6d37b36ff24a8a50)`()` | 
`public void `[`putWordAsCategory`](#classtrie_1_1Trie__t_1aa625ac20f59067475a3be018b5cdcac6)`(const std::string &,char,unsigned int)` | 
`public void `[`putWordAsStore`](#classtrie_1_1Trie__t_1af32f8e6730db792cd6d41143a2b2a273)`(const std::string &,char,unsigned int)` | 
`public void `[`setSearchLimitThreshold`](#classtrie_1_1Trie__t_1ad3efa538448915e9bf531441b0efc32e)`(int)` | 
`public void `[`setFuzzyLimitThreshold`](#classtrie_1_1Trie__t_1a273a9b1e91517325ae0c979590de9fcb)`(int)` | 
`public void `[`buildActiveNodeSet`](#classtrie_1_1Trie__t_1acfd77fea6c73973ff98d44dea8c05351)`()` | 
`public void `[`printData`](#classtrie_1_1Trie__t_1a7f46e1d17a8dde31e8874e914d046e71)`()` | 
`public std::priority_queue< `[`Occurrence_t](#structtrie_1_1Occurrence__t), std::vector< [Occurrence_t](#structtrie_1_1Occurrence__t) >, [OccurrencePriorityComparator_t`](#structtrie_1_1OccurrencePriorityComparator__t)` > `[`searchSimilarKeyword`](#classtrie_1_1Trie__t_1a3d6f74607db9509da5abd6e5117591a3)`(const std::string &,Type type)` | 
`public std::set< `[`UData::Category_t](#structUData_1_1Category__t), [UData::CategoryComparator_t`](#structUData_1_1CategoryComparator__t)` > `[`getCategoriesByStore`](#classtrie_1_1Trie__t_1a00bd519847f96b60da5999f5eebee23c)`(unsigned int id)` | 
`public std::set< `[`UData::Store_t](#structUData_1_1Store__t), [UData::StoreComparator_t`](#structUData_1_1StoreComparator__t)` > `[`getStoresByCategory`](#classtrie_1_1Trie__t_1ad0c4c140f01e30d7c1345e11f58f1e44)`(unsigned int id)` | 
`public bool `[`addRelation`](#classtrie_1_1Trie__t_1a5e335f7bcd51cc3b820bb94931464927)`(unsigned int,unsigned int)` | 
`public bool `[`removeRelation`](#classtrie_1_1Trie__t_1ae285c1a579de36f9a00a0897713d8837)`(unsigned int,unsigned int)` | 
`public bool `[`insertCategory`](#classtrie_1_1Trie__t_1a17d578a722beb7fe42b73e3432cd4bd2)`(unsigned int,const std::string &)` | 
`public bool `[`insertStore`](#classtrie_1_1Trie__t_1a76758455900a50763a42d708e95e33d3)`(unsigned int,const std::string &,const std::string &,const std::string &,const std::string &)` | 
`public bool `[`updateStore`](#classtrie_1_1Trie__t_1a16173b416718e1f62a780fbf1a534a69)`(unsigned int,const std::string &,const std::string &,const std::string &,const std::string &)` | 
`public bool `[`updateCategory`](#classtrie_1_1Trie__t_1ad3912c6926d5c7fced0fad9351f98ee0)`(unsigned int,const std::string &)` | 
`public bool `[`removeStore`](#classtrie_1_1Trie__t_1a4cd52573eaa01f4144e53382cb8c9b7c)`(unsigned int,bool)` | 
`public bool `[`removeCategory`](#classtrie_1_1Trie__t_1a3dd93bf212cf24e5d779c2c3cc3a42b6)`(unsigned int,bool)` | 
`public `[`UData::Store_t`](#structUData_1_1Store__t)` `[`getStore`](#classtrie_1_1Trie__t_1a2f4c6eaf8c7e82162b7d2bf8324215a0)`(unsigned int)` | 
`public `[`UData::Category_t`](#structUData_1_1Category__t)` `[`getCategory`](#classtrie_1_1Trie__t_1a69b0bd52680c7754e6a6f4c3fadce5b7)`(unsigned int)` | 

## Members

#### `public  `[`Trie_t`](#classtrie_1_1Trie__t_1a5de6b677c32073f299be3c59cb722981)`()` 

#### `public void `[`encodeCharacters`](#classtrie_1_1Trie__t_1acc0545c3bcba9b6cf045450a3a154411)`(const std::string &)` 

#### `public void `[`addStopWords`](#classtrie_1_1Trie__t_1a804d74ea84fa95fefe9f3516831f40e7)`(const std::string &)` 

#### `public bool `[`isStopWord`](#classtrie_1_1Trie__t_1abcc65ebc46c344395041af08568f418a)`(std::string)` 

#### `public void `[`printTrie`](#classtrie_1_1Trie__t_1a24b16e350ae27a7e6d37b36ff24a8a50)`()` 

#### `public void `[`putWordAsCategory`](#classtrie_1_1Trie__t_1aa625ac20f59067475a3be018b5cdcac6)`(const std::string &,char,unsigned int)` 

#### `public void `[`putWordAsStore`](#classtrie_1_1Trie__t_1af32f8e6730db792cd6d41143a2b2a273)`(const std::string &,char,unsigned int)` 

#### `public void `[`setSearchLimitThreshold`](#classtrie_1_1Trie__t_1ad3efa538448915e9bf531441b0efc32e)`(int)` 

#### `public void `[`setFuzzyLimitThreshold`](#classtrie_1_1Trie__t_1a273a9b1e91517325ae0c979590de9fcb)`(int)` 

#### `public void `[`buildActiveNodeSet`](#classtrie_1_1Trie__t_1acfd77fea6c73973ff98d44dea8c05351)`()` 

#### `public void `[`printData`](#classtrie_1_1Trie__t_1a7f46e1d17a8dde31e8874e914d046e71)`()` 

#### `public std::priority_queue< `[`Occurrence_t](#structtrie_1_1Occurrence__t), std::vector< [Occurrence_t](#structtrie_1_1Occurrence__t) >, [OccurrencePriorityComparator_t`](#structtrie_1_1OccurrencePriorityComparator__t)` > `[`searchSimilarKeyword`](#classtrie_1_1Trie__t_1a3d6f74607db9509da5abd6e5117591a3)`(const std::string &,Type type)` 

#### `public std::set< `[`UData::Category_t](#structUData_1_1Category__t), [UData::CategoryComparator_t`](#structUData_1_1CategoryComparator__t)` > `[`getCategoriesByStore`](#classtrie_1_1Trie__t_1a00bd519847f96b60da5999f5eebee23c)`(unsigned int id)` 

#### `public std::set< `[`UData::Store_t](#structUData_1_1Store__t), [UData::StoreComparator_t`](#structUData_1_1StoreComparator__t)` > `[`getStoresByCategory`](#classtrie_1_1Trie__t_1ad0c4c140f01e30d7c1345e11f58f1e44)`(unsigned int id)` 

#### `public bool `[`addRelation`](#classtrie_1_1Trie__t_1a5e335f7bcd51cc3b820bb94931464927)`(unsigned int,unsigned int)` 

#### `public bool `[`removeRelation`](#classtrie_1_1Trie__t_1ae285c1a579de36f9a00a0897713d8837)`(unsigned int,unsigned int)` 

#### `public bool `[`insertCategory`](#classtrie_1_1Trie__t_1a17d578a722beb7fe42b73e3432cd4bd2)`(unsigned int,const std::string &)` 

#### `public bool `[`insertStore`](#classtrie_1_1Trie__t_1a76758455900a50763a42d708e95e33d3)`(unsigned int,const std::string &,const std::string &,const std::string &,const std::string &)` 

#### `public bool `[`updateStore`](#classtrie_1_1Trie__t_1a16173b416718e1f62a780fbf1a534a69)`(unsigned int,const std::string &,const std::string &,const std::string &,const std::string &)` 

#### `public bool `[`updateCategory`](#classtrie_1_1Trie__t_1ad3912c6926d5c7fced0fad9351f98ee0)`(unsigned int,const std::string &)` 

#### `public bool `[`removeStore`](#classtrie_1_1Trie__t_1a4cd52573eaa01f4144e53382cb8c9b7c)`(unsigned int,bool)` 

#### `public bool `[`removeCategory`](#classtrie_1_1Trie__t_1a3dd93bf212cf24e5d779c2c3cc3a42b6)`(unsigned int,bool)` 

#### `public `[`UData::Store_t`](#structUData_1_1Store__t)` `[`getStore`](#classtrie_1_1Trie__t_1a2f4c6eaf8c7e82162b7d2bf8324215a0)`(unsigned int)` 

#### `public `[`UData::Category_t`](#structUData_1_1Category__t)` `[`getCategory`](#classtrie_1_1Trie__t_1a69b0bd52680c7754e6a6f4c3fadce5b7)`(unsigned int)` 

# class `trie::TrieNode_t` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`TrieNode_t`](#classtrie_1_1TrieNode__t_1aa3c1f1565147210c26ec1c971f3697cd)`(unsigned int)` | 
`public unsigned int `[`getContent`](#classtrie_1_1TrieNode__t_1ab43e8d6363e9344b470cd56b7ece1eb1)`()` | 
`public std::vector< `[`TrieNode_t`](#classtrie_1_1TrieNode__t)` * > `[`getChildren`](#classtrie_1_1TrieNode__t_1a6bbcdbc05975ef6f560ca5bcdf7c6b0d)`()` | 
`public `[`TrieNode_t`](#classtrie_1_1TrieNode__t)` * `[`insertNReturnChild`](#classtrie_1_1TrieNode__t_1af71372917a417ebec8afa907e9a3018d)`(unsigned int)` | 
`public `[`TrieNode_t`](#classtrie_1_1TrieNode__t)` * `[`getChild`](#classtrie_1_1TrieNode__t_1a0b3ff127f5cdcd036c8e831d4bb2b1db)`(unsigned int)` | 
`public bool `[`isEndOfWord`](#classtrie_1_1TrieNode__t_1ad1995f7691f40ea8c73bd0b2de98be5a)`()` | 
`public bool `[`isEndOfCategory`](#classtrie_1_1TrieNode__t_1a613acf1f9eabed9c1af5dcbfcfa95bc7)`()` | 
`public bool `[`isEndOfStore`](#classtrie_1_1TrieNode__t_1a9a5ebfc0530654f9f4590f2711121050)`()` | 
`public void `[`setEndOfCategory`](#classtrie_1_1TrieNode__t_1a805f6142576e5a8942bca6a7595902ee)`(bool)` | 
`public void `[`setEndOfStore`](#classtrie_1_1TrieNode__t_1a1e87a5a9414d74da79c9da9afdcf33a7)`(bool)` | 
`public void `[`buildOccurrences`](#classtrie_1_1TrieNode__t_1a9f070a8f71075d029a3d59734aaa6104)`(Type)` | 
`public void `[`addOccurrence`](#classtrie_1_1TrieNode__t_1a972f9030382af9162e26bbcd3e4b4365)`(char,unsigned int,Type)` | 
`public std::list< const std::list< `[`Occurrence_t`](#structtrie_1_1Occurrence__t)` > * > `[`getOccurences`](#classtrie_1_1TrieNode__t_1a234021d00928e07fa02379bbff2536fd)`(Type)` | 

## Members

#### `public  `[`TrieNode_t`](#classtrie_1_1TrieNode__t_1aa3c1f1565147210c26ec1c971f3697cd)`(unsigned int)` 

#### `public unsigned int `[`getContent`](#classtrie_1_1TrieNode__t_1ab43e8d6363e9344b470cd56b7ece1eb1)`()` 

#### `public std::vector< `[`TrieNode_t`](#classtrie_1_1TrieNode__t)` * > `[`getChildren`](#classtrie_1_1TrieNode__t_1a6bbcdbc05975ef6f560ca5bcdf7c6b0d)`()` 

#### `public `[`TrieNode_t`](#classtrie_1_1TrieNode__t)` * `[`insertNReturnChild`](#classtrie_1_1TrieNode__t_1af71372917a417ebec8afa907e9a3018d)`(unsigned int)` 

#### `public `[`TrieNode_t`](#classtrie_1_1TrieNode__t)` * `[`getChild`](#classtrie_1_1TrieNode__t_1a0b3ff127f5cdcd036c8e831d4bb2b1db)`(unsigned int)` 

#### `public bool `[`isEndOfWord`](#classtrie_1_1TrieNode__t_1ad1995f7691f40ea8c73bd0b2de98be5a)`()` 

#### `public bool `[`isEndOfCategory`](#classtrie_1_1TrieNode__t_1a613acf1f9eabed9c1af5dcbfcfa95bc7)`()` 

#### `public bool `[`isEndOfStore`](#classtrie_1_1TrieNode__t_1a9a5ebfc0530654f9f4590f2711121050)`()` 

#### `public void `[`setEndOfCategory`](#classtrie_1_1TrieNode__t_1a805f6142576e5a8942bca6a7595902ee)`(bool)` 

#### `public void `[`setEndOfStore`](#classtrie_1_1TrieNode__t_1a1e87a5a9414d74da79c9da9afdcf33a7)`(bool)` 

#### `public void `[`buildOccurrences`](#classtrie_1_1TrieNode__t_1a9f070a8f71075d029a3d59734aaa6104)`(Type)` 

#### `public void `[`addOccurrence`](#classtrie_1_1TrieNode__t_1a972f9030382af9162e26bbcd3e4b4365)`(char,unsigned int,Type)` 

#### `public std::list< const std::list< `[`Occurrence_t`](#structtrie_1_1Occurrence__t)` > * > `[`getOccurences`](#classtrie_1_1TrieNode__t_1a234021d00928e07fa02379bbff2536fd)`(Type)` 

# struct `trie::ActiveNode_t` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`TrieNode_t`](#classtrie_1_1TrieNode__t)` * `[`node`](#structtrie_1_1ActiveNode__t_1ad0756df7e15cf7b3eb69087c53e3a6b4) | 
`public mutable int `[`editDistance`](#structtrie_1_1ActiveNode__t_1ab72477e4248864e89aec5f8fdd02c202) | 
`public mutable int `[`positionDistance`](#structtrie_1_1ActiveNode__t_1ab86d402decf8ec5484893ae77ebf8f8c) | 
`public  `[`ActiveNode_t`](#structtrie_1_1ActiveNode__t_1a91ccfa1c782fe00e3ae4b8179b358f49)`(`[`TrieNode_t`](#classtrie_1_1TrieNode__t)` *,int)` | 
`public  `[`ActiveNode_t`](#structtrie_1_1ActiveNode__t_1aab42b73cc48adf726fceb40de4b870d9)`(`[`TrieNode_t`](#classtrie_1_1TrieNode__t)` *,int,int)` | 
`public bool `[`operator<`](#structtrie_1_1ActiveNode__t_1ae6397306545a778f889ae71819e030f7)`(const `[`ActiveNode_t`](#structtrie_1_1ActiveNode__t)` &) const` | 

## Members

#### `public `[`TrieNode_t`](#classtrie_1_1TrieNode__t)` * `[`node`](#structtrie_1_1ActiveNode__t_1ad0756df7e15cf7b3eb69087c53e3a6b4) 

#### `public mutable int `[`editDistance`](#structtrie_1_1ActiveNode__t_1ab72477e4248864e89aec5f8fdd02c202) 

#### `public mutable int `[`positionDistance`](#structtrie_1_1ActiveNode__t_1ab86d402decf8ec5484893ae77ebf8f8c) 

#### `public  `[`ActiveNode_t`](#structtrie_1_1ActiveNode__t_1a91ccfa1c782fe00e3ae4b8179b358f49)`(`[`TrieNode_t`](#classtrie_1_1TrieNode__t)` *,int)` 

#### `public  `[`ActiveNode_t`](#structtrie_1_1ActiveNode__t_1aab42b73cc48adf726fceb40de4b870d9)`(`[`TrieNode_t`](#classtrie_1_1TrieNode__t)` *,int,int)` 

#### `public bool `[`operator<`](#structtrie_1_1ActiveNode__t_1ae6397306545a778f889ae71819e030f7)`(const `[`ActiveNode_t`](#structtrie_1_1ActiveNode__t)` &) const` 

# struct `trie::ActiveNodeComparator_t` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public bool `[`operator()`](#structtrie_1_1ActiveNodeComparator__t_1ac7b71aa239b687b42286f09c332415ac)`(const `[`ActiveNode_t`](#structtrie_1_1ActiveNode__t)` &,const `[`ActiveNode_t`](#structtrie_1_1ActiveNode__t)` &) const` | 

## Members

#### `public bool `[`operator()`](#structtrie_1_1ActiveNodeComparator__t_1ac7b71aa239b687b42286f09c332415ac)`(const `[`ActiveNode_t`](#structtrie_1_1ActiveNode__t)` &,const `[`ActiveNode_t`](#structtrie_1_1ActiveNode__t)` &) const` 

# struct `trie::Occurrence_t` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public unsigned int `[`itemRef`](#structtrie_1_1Occurrence__t_1a43960f97cafebe64c26c982c08cfba07) | 
`public mutable char `[`positionOnItem`](#structtrie_1_1Occurrence__t_1ad437b9d4a0706be3198be71758f82be0) | 
`public mutable int `[`weight`](#structtrie_1_1Occurrence__t_1a6965ab9a75e4890037aeaa352700ba30) | 
`public mutable Type `[`type`](#structtrie_1_1Occurrence__t_1a5f621787f85ec4a976004b5321eac41c) | 
`public  `[`Occurrence_t`](#structtrie_1_1Occurrence__t_1a29ea384004224301476367000f06c816)`(unsigned int,char)` | 
`public  `[`Occurrence_t`](#structtrie_1_1Occurrence__t_1a63b33fa23c261f3597880450f3925d94)`(unsigned int,char,Type)` | 
`public bool `[`operator<`](#structtrie_1_1Occurrence__t_1a5cc0e97b16d080695ef9e1a7ef28c0b5)`(const `[`Occurrence_t`](#structtrie_1_1Occurrence__t)` &) const` | 

## Members

#### `public unsigned int `[`itemRef`](#structtrie_1_1Occurrence__t_1a43960f97cafebe64c26c982c08cfba07) 

#### `public mutable char `[`positionOnItem`](#structtrie_1_1Occurrence__t_1ad437b9d4a0706be3198be71758f82be0) 

#### `public mutable int `[`weight`](#structtrie_1_1Occurrence__t_1a6965ab9a75e4890037aeaa352700ba30) 

#### `public mutable Type `[`type`](#structtrie_1_1Occurrence__t_1a5f621787f85ec4a976004b5321eac41c) 

#### `public  `[`Occurrence_t`](#structtrie_1_1Occurrence__t_1a29ea384004224301476367000f06c816)`(unsigned int,char)` 

#### `public  `[`Occurrence_t`](#structtrie_1_1Occurrence__t_1a63b33fa23c261f3597880450f3925d94)`(unsigned int,char,Type)` 

#### `public bool `[`operator<`](#structtrie_1_1Occurrence__t_1a5cc0e97b16d080695ef9e1a7ef28c0b5)`(const `[`Occurrence_t`](#structtrie_1_1Occurrence__t)` &) const` 

# struct `trie::OccurrencePriorityComparator_t` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public const bool `[`operator()`](#structtrie_1_1OccurrencePriorityComparator__t_1a5aa9e9a1b9429b496241f78e4a6b127c)`(const `[`Occurrence_t`](#structtrie_1_1Occurrence__t)` &,const `[`Occurrence_t`](#structtrie_1_1Occurrence__t)` &) const` | 

## Members

#### `public const bool `[`operator()`](#structtrie_1_1OccurrencePriorityComparator__t_1a5aa9e9a1b9429b496241f78e4a6b127c)`(const `[`Occurrence_t`](#structtrie_1_1Occurrence__t)` &,const `[`Occurrence_t`](#structtrie_1_1Occurrence__t)` &) const` 

# namespace `UData` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`buildJson`](#unionData_8hpp_1a7d1e2e5109eef92e6766586930c5216d)`(`[`Store_t`](#structUData_1_1Store__t)` &)`            | 
`public void `[`buildJson`](#unionData_8hpp_1a97f4b14b731648377ea58a6877a251c9)`(`[`Category_t`](#structUData_1_1Category__t)` &)`            | 
`public void `[`updateAll`](#unionData_8hpp_1a621272778bc2f25975499e5d29cef987)`(`[`Store_t`](#structUData_1_1Store__t)` &,const std::string &,const std::string &,const std::string &,const std::string &)`            | 
`public void `[`updateAll`](#unionData_8hpp_1a69f96a50aeee4890f670360fd427027b)`(`[`Category_t`](#structUData_1_1Category__t)` &,const std::string &)`            | 
`public std::vector< std::string > `[`split`](#unionData_8hpp_1aa8045ec56a85662295128cccec2ea7dc)`(const std::string &,char delimiter)`            | 
`public unsigned int `[`string2unsigned`](#unionData_8hpp_1ac75ef5a1ab7527bc4bd789864eacf186)`(const std::string &)`            | 
`struct `[`UData::Category_t`](#structUData_1_1Category__t) | 
`struct `[`UData::CategoryComparator_t`](#structUData_1_1CategoryComparator__t) | 
`struct `[`UData::Store_t`](#structUData_1_1Store__t) | 
`struct `[`UData::StoreComparator_t`](#structUData_1_1StoreComparator__t) | 

## Members

#### `public void `[`buildJson`](#unionData_8hpp_1a7d1e2e5109eef92e6766586930c5216d)`(`[`Store_t`](#structUData_1_1Store__t)` &)` 

#### `public void `[`buildJson`](#unionData_8hpp_1a97f4b14b731648377ea58a6877a251c9)`(`[`Category_t`](#structUData_1_1Category__t)` &)` 

#### `public void `[`updateAll`](#unionData_8hpp_1a621272778bc2f25975499e5d29cef987)`(`[`Store_t`](#structUData_1_1Store__t)` &,const std::string &,const std::string &,const std::string &,const std::string &)` 

#### `public void `[`updateAll`](#unionData_8hpp_1a69f96a50aeee4890f670360fd427027b)`(`[`Category_t`](#structUData_1_1Category__t)` &,const std::string &)` 

#### `public std::vector< std::string > `[`split`](#unionData_8hpp_1aa8045ec56a85662295128cccec2ea7dc)`(const std::string &,char delimiter)` 

#### `public unsigned int `[`string2unsigned`](#unionData_8hpp_1ac75ef5a1ab7527bc4bd789864eacf186)`(const std::string &)` 

# struct `UData::Category_t` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public unsigned int `[`id`](#structUData_1_1Category__t_1ade647eb44ecba6d03ffffb13829bc8cf) | 
`public std::string `[`name`](#structUData_1_1Category__t_1a5d1606e9f8802953345cf06c2e833963) | 
`public std::string `[`json`](#structUData_1_1Category__t_1aba7b882371a155a411e75dda0f599494) | 
`public bool `[`active`](#structUData_1_1Category__t_1ac9390eae6ef29fc1c4cffbbf6be58029) | 
`public  `[`Category_t`](#structUData_1_1Category__t_1a6317dffdd20ac3aaf56d2c63abcbba91)`(unsigned int,const std::string &)` | 
`public  `[`Category_t`](#structUData_1_1Category__t_1a58b6784f1cce8a31a02b3f75d91723f3)`(unsigned int,const std::string &,const std::string &)` | 

## Members

#### `public unsigned int `[`id`](#structUData_1_1Category__t_1ade647eb44ecba6d03ffffb13829bc8cf) 

#### `public std::string `[`name`](#structUData_1_1Category__t_1a5d1606e9f8802953345cf06c2e833963) 

#### `public std::string `[`json`](#structUData_1_1Category__t_1aba7b882371a155a411e75dda0f599494) 

#### `public bool `[`active`](#structUData_1_1Category__t_1ac9390eae6ef29fc1c4cffbbf6be58029) 

#### `public  `[`Category_t`](#structUData_1_1Category__t_1a6317dffdd20ac3aaf56d2c63abcbba91)`(unsigned int,const std::string &)` 

#### `public  `[`Category_t`](#structUData_1_1Category__t_1a58b6784f1cce8a31a02b3f75d91723f3)`(unsigned int,const std::string &,const std::string &)` 

# struct `UData::CategoryComparator_t` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public bool `[`operator()`](#structUData_1_1CategoryComparator__t_1a2d5035424519642f0d4c0245834a9b8b)`(const `[`Category_t`](#structUData_1_1Category__t)` &,const `[`Category_t`](#structUData_1_1Category__t)` &) const` | 

## Members

#### `public bool `[`operator()`](#structUData_1_1CategoryComparator__t_1a2d5035424519642f0d4c0245834a9b8b)`(const `[`Category_t`](#structUData_1_1Category__t)` &,const `[`Category_t`](#structUData_1_1Category__t)` &) const` 

# struct `UData::Store_t` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public unsigned int `[`id`](#structUData_1_1Store__t_1a62f09e97d8616610eebb0f8de7db8fdf) | 
`public std::string `[`name`](#structUData_1_1Store__t_1a05ac903d156a14c73c38c08ce2aefa67) | 
`public std::string `[`lat`](#structUData_1_1Store__t_1a8c8b3477ca25e0f418c78b830b496959) | 
`public std::string `[`lng`](#structUData_1_1Store__t_1a473af4b2a3d84be0264b4eee6cd9b4fa) | 
`public std::string `[`max_radius`](#structUData_1_1Store__t_1afe7c256777e645709827834732e59b3c) | 
`public std::string `[`json`](#structUData_1_1Store__t_1ad0256f8f1cbda2fa2347f0dff3a5a6ad) | 
`public bool `[`active`](#structUData_1_1Store__t_1aedc15a041a7a6b5f3cb0cd41224d862c) | 
`public  `[`Store_t`](#structUData_1_1Store__t_1a4a52e7fb0024cf25559103652b03857d)`(unsigned int,const std::string &,const std::string &,const std::string &,const std::string &)` | 
`public  `[`Store_t`](#structUData_1_1Store__t_1a8030929e80bd2f2f19d827aac11bbd46)`(unsigned int,const std::string &,const std::string &,const std::string &,const std::string &,const std::string &)` | 

## Members

#### `public unsigned int `[`id`](#structUData_1_1Store__t_1a62f09e97d8616610eebb0f8de7db8fdf) 

#### `public std::string `[`name`](#structUData_1_1Store__t_1a05ac903d156a14c73c38c08ce2aefa67) 

#### `public std::string `[`lat`](#structUData_1_1Store__t_1a8c8b3477ca25e0f418c78b830b496959) 

#### `public std::string `[`lng`](#structUData_1_1Store__t_1a473af4b2a3d84be0264b4eee6cd9b4fa) 

#### `public std::string `[`max_radius`](#structUData_1_1Store__t_1afe7c256777e645709827834732e59b3c) 

#### `public std::string `[`json`](#structUData_1_1Store__t_1ad0256f8f1cbda2fa2347f0dff3a5a6ad) 

#### `public bool `[`active`](#structUData_1_1Store__t_1aedc15a041a7a6b5f3cb0cd41224d862c) 

#### `public  `[`Store_t`](#structUData_1_1Store__t_1a4a52e7fb0024cf25559103652b03857d)`(unsigned int,const std::string &,const std::string &,const std::string &,const std::string &)` 

#### `public  `[`Store_t`](#structUData_1_1Store__t_1a8030929e80bd2f2f19d827aac11bbd46)`(unsigned int,const std::string &,const std::string &,const std::string &,const std::string &,const std::string &)` 

# struct `UData::StoreComparator_t` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public bool `[`operator()`](#structUData_1_1StoreComparator__t_1ac5f1782cafe92121cf50d547d0eb09b2)`(const `[`Store_t`](#structUData_1_1Store__t)` &,const `[`Store_t`](#structUData_1_1Store__t)` &) const` | 

## Members

#### `public bool `[`operator()`](#structUData_1_1StoreComparator__t_1ac5f1782cafe92121cf50d547d0eb09b2)`(const `[`Store_t`](#structUData_1_1Store__t)` &,const `[`Store_t`](#structUData_1_1Store__t)` &) const` 

Generated by [Moxygen](https://sourcey.com/moxygen)