# Introduzione
Il progetto richiedeva l’implementazione di una classe che implementi un set, cioè una collezione di dati che non ammette duplicati, di elementi generici T.
## Scelte implementative e di design importanti
Visto che era necessario implementare una collezione di dati che non ammette duplicati, oltre a templare la classe sul tipo dell’elemento T, ho anche aggiunto un template Equal che si occupa di gestire l’uguaglianza fra gli elementi del set, permettendomi di controllare se due elementi sono uguali.<br>
Per l’implementazione ho deciso di utilizzare un array dinamico chiamato _array per contenere gli elementi del set, visto che era richiesto di non usare le liste.<br>
Per cercare di rendere più efficiente la gestione della memoria di questo array dinamico, ed evitare troppe copie quando viene ridimensionato, ho deciso di utilizzare una politica di ridimensionamento simile ad altre implementazioni dove viene usato l’array dinamico. Aumentando la dimensione 
dell’array di 2 quando viene aggiunto un elemento e l’array è pieno (in altre implementazioni viene usato 1.5 perché in molti casi più efficiente però ho deciso comunque di tenere 2) e diminuire la dimensione di 1/4 quando viene rimosso un elemento e si è arrivati a metà o meno della capacità, 
oltre a questo ho deciso di mettere un limite di 200 a quanto viene aumentata la capacità dell’array dinamico per evitare di aumentare troppo la dimensione.<br>
Per gestire questo array dinamico ho utilizzato altre due variabili, _capacity per indicare la dimensione effettiva dell’array dinamico e _size per indicare il numero degli elementi dentro l’array e quindi del set.<br>
Per ridimensionare l’array dinamico uso un metodo di supporto nascosto dall’interfaccia pubblica chiamato resize, metodo che si occupa di gestire il ridimensionamento dell’array dinamico.<br>
Per i metodi da implementare ho deciso di mettere come valore di ritorno per i metodi add/remove un booleano questo perché è possibile che l’add non inserisca l’elemento quando è già presente e nella remove non viene rimosso un elemento che non esiste nel set.<br>
Infine, ho implementato il const_iterator mediante i puntatori questo perché la classe set internamente viene implementata con un array dinamico e l’accesso ai dati è di tipo random perché implementiamo l’operatore [ ] costante.<br>
