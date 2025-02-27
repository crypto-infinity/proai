# InsuraPro Solutions, CRM per impresa di assicurazioni

InsuraPro Solutions si dedica a migliorare l'efficienza e la qualità del servizio clienti per le imprese di assicurazioni, sviluppando un avanzato sistema di Customer Relationship Management (CRM) che facilita la gestione delle informazioni sui clienti e delle loro interazioni con l'azienda.

Le imprese di assicurazioni necessitano di un metodo sistematico e centralizzato per gestire le informazioni sui clienti e tracciare le interazioni. Molti sistemi attuali sono frammentati o non user-friendly, ostacolando l’efficacia operativa e la soddisfazione del cliente.

InsuraPro Solutions offrirà un’applicazione console interattiva sviluppata in C++ che permetterà agli utenti di gestire le informazioni sui clienti e le loro interazioni in modo efficiente e intuitivo, migliorando così il servizio clienti e la gestione interna.

# Requisiti del Progetto:

* **OOP in C++:** Implementare i concetti di OOP per una struttura robusta e flessibile.
* **Struttura Dati:** Creare una struttura di dati per memorizzare le informazioni sui clienti e le loro interazioni.
* **Interfaccia Utente:** Sviluppare un’interfaccia da linea di comando interattiva e intuitiva.

## Funzionalità:

* **Aggiunta di un Cliente:** Inserimento di nuovi clienti nel CRM.
* **Visualizzazione dei Clienti:** Visualizzare tutti i clienti presenti.
* **Modifica di un Cliente:** Modificare i dettagli di un cliente esistente.
* **Eliminazione di un Cliente:** Rimuovere clienti dal CRM.
* **Ricerca di un Cliente:** Cercare clienti per nome o cognome.
* **Gestione delle Interazioni:** Aggiungere, visualizzare e cercare interazioni per ogni cliente (per interazioni si intendono gli appuntamenti da parte della forza vendita e i contratti stipulati).
* **Salvataggio e Caricamento Dati:** Salvare i dati dei clienti e delle interazioni in un file (testo o CSV) e caricarli all’avvio.

* **Interfaccia Utente:** L’interfaccia sarà basata su riga di comando, con un menu principale che offre opzioni chiare per tutte le operazioni necessarie, assicurando un'esperienza utente fluida e accessibile.

<br>


# L'implementazione:

Il codice implementa **`InsuraPro Solutions`**, 'applicazione avanzata e resiliente per la gestione di un avanzato sistema CRM tramite un'interfaccia a linea di comando. Il programma è scritto in C++ e utilizza i principi della programmazione orientata agli oggetti (OOP).

**Classi**

Il codice definisce cinque classi principali, raccolte in un namespace dedicato `InsuraPro`:

* **`Contact`:** Rappresenta un singolo contatto, memorizzando informazioni come nome, cognome, email, telefono, indirizzo e sito web. Include metodi per validare e impostare i dati del contatto.

* **`Client:`** Rappresenta un cliente specifico, memorizzando informazioni sull'azienda come nome, PIVA e altro. Include metodi per la validazione dei dati e relativa impostazione.

* **`Interaction:`** Rappresenta un'interazione verso un cliente specifico, includendo metodi per la validazione dei dati e relativa impostazione.

* **`Utility:`** Fornisce una serie di funzioni di supporto, tra cui la visualizzazione del menu di aiuto e la generazione di stringhe casuali per gli ID dei contatti.

* **`Input:`** Fornisce una serie di funzioni di supporto per gli input dell'utente, tra cui i metodi di acquisizione, gestione e validazione dell'input utente.

**Dipendenze:**

Per lo sviluppo del software sono state utilizzate le seguenti dipendenze di **C++**:

* **`stdc++:`** viene utilizzato per interagire con la standard library di C++, per l'uso di tipi e funzioni standard del linguaggio
* **`regex:`** viene utilizzato per lavorare con le espressioni regolari, in particolare
per la convalida di *indirizzi e-mail* e *numeri di telefono*.
* **`filesystem:`** viene utilizzata per l'interazione con l'OS, la validazione dei file CSV e relativa gestione.
* **`tuple:`** viene utilizzato per interagire con le tuple di C++, utili nel software per l'associazione ID/selezione utente.
* **`rapidcsv:`** viene utilizzata per lavorare sui file CSV in stream, ottimizzando la gestione della memoria. Essa permette di ottenere e/o inserire direttamente valori nel CSV, per cella, per riga oppure operare sull'intero documento, ottenendo valori come il numero di righe presenti nel file.

Queste dipendenze sono state scelte per le seguenti ragioni:

* Sono ampiamente utilizzate e ben documentate, il che ne semplifica l'utilizzo e la risoluzione dei problemi.
* Forniscono le funzionalità necessarie per l'implementazione del CRM, come la lettura/scrittura degli oggetti e la relativa gestione.
* Ottimizzano l'uso della memoria e consentono di semplificare l'esperienza utente e lo sviluppo dell'app.

Le espressioni regolari sono state utilizzate per convalidare indirizzi email e numeri di telefono. Questo assicura che i dati inseriti siano nel formato corretto e coerenti, migliorando l'affidabilità e la qualità dei dati nel CRM.

**Modificabilità:**

Le espressioni regolari sono definite come costanti. Questo rende facile modificarle in futuro se i requisiti di validazione dovessero cambiare.

Esempi:

* **`EMAIL_REGEX:`** Definisce il formato valido per un indirizzo email.
* **`PHONE_REGEX:`** Definisce il formato valido per un numero di telefono.

Per modificare le espressioni regolari, è sufficiente aggiornare il valore delle costanti con la nuova espressione desiderata.

**Definizione delle Classi:**

***Contact***

La classe **`Contact`** rappresenta un singolo contatto nel CRM. Memorizza informazioni come nome, cognome, email, telefono, indirizzo e sito web. Include metodi per validare e impostare i dati del contatto, nonchè il mantenimento della relazione con l'oggetto `InsuraPro::Client` relativo.


**Attributi:**

* `id`: Identificativo univoco del contatto.
* `name`: Nome del contatto (obbligatorio).
* `surname`: Cognome del contatto (opzionale).
* `_address`: Indirizzo del contatto (opzionale).
* `_email`: Email del contatto (opzionale).
* `_phone`: Numero di telefono del contatto (opzionale).

* `client_id`: ID di associazione con il cliente.


**Esempio di utilizzo:**

`Contact* nuovo_contatto = new Contact("Mario", surname="Rossi", email="mario.rossi@example.com", phone="+39 333 1234567")`

**Validazione degli input:**

La classe include metodi per validare e impostare i dati del contatto, come `set_name()`, `set_email()`, e gli altri relativi setters.

Se l'input non è considerato valido dalle condizioni indicate, viene restituita un'eccezione di tipo `std::invalid_argument`, che il codice gestisce nella classe `input.h`.

I contatti sono memorizzati in un file CSV dedicato, `contacts.csv`.

***Client***

La classe **`Client`** rappresenta un cliente specifico nel CRM. Memorizza informazioni sull'azienda come nome, PIVA e altro. Include metodi per validare e impostare i dati del cliente. Essa tiene traccia delle relazioni 1:Many tra un cliente e le sue interazioni.

**Attributi:**

* `id`: Identificativo univoco del cliente.
* `company_name`: Nome dell'azienda (obbligatorio).
* `vat_number`: Partita IVA dell'azienda (obbligatorio).
* `_address`: Indirizzo dell'azienda (opzionale).
* `_email`: Email dell'azienda (opzionale).
* `_phone`: Numero di telefono dell'azienda (opzionale).

* `interaction_ids`: Vettore rappresentante gli ID delle interazioni collegate al cliente.

**Esempio di utilizzo:**

`Client* nuovo_cliente = new Client("Tech Solutions", vat_number="IT12345678901", email="info@techsolutions.com", phone="+39 055 1234567")`

**Validazione degli input:**

La classe include metodi per validare e impostare i dati del cliente, come `set_company_name()`, `set_vat_number()`, e gli altri relativi setters.

Se l'input non è considerato valido dalle condizioni indicate, viene restituita un'eccezione di tipo `std::invalid_argument`, che il codice gestisce nella classe `input.h`.

Essa gestisce le associazioni con le interazioni nel campo `interaction_ids` del CSV associato `clients.h`, il quale contiene l'elenco dei clienti censiti.

***Interaction***

La classe **`Interaction`** rappresenta un'interazione verso un cliente specifico, includendo metodi per la validazione dei dati e relativa impostazione.

**Attributi:**

* `id`: Identificativo univoco dell'interazione.
* `name`: Nome dell'interazione.
* `date`: Data dell'interazione.
* `type`: Tipo di interazione (es. appuntamento, contratto).
* `notes`: Note aggiuntive sull'interazione (opzionale).

**Esempio di utilizzo:**

`Interaction* nuova_interazione = new Interaction(name="Interazione1", date="2025-02-27", type="appuntamento", notes="Discussione sui nuovi prodotti")`

**Validazione degli input:**

La classe include metodi per validare e impostare i dati dell'interazione, come `set_date()`, `set_type()`, e gli altri relativi setters.

Se l'input non è considerato valido dalle condizioni indicate, viene restituita un'eccezione di tipo `std::invalid_argument`, che il codice gestisce nella classe `input.h`.

***Utility***

La classe **`Utility`** fornisce una serie di funzioni di supporto, tra cui la visualizzazione del menu di aiuto e la generazione di stringhe casuali per gli ID dei contatti.

Essa definisce e propaga alcune variabili e costanti utilizzate nel software, ad esempio le REGEX e gli schema per i file CSV.

**Funzioni principali:**

* `show_help()`: Visualizza il menu di aiuto.
* `toLower()`: Restituisce una versione lowercase della stringa in input.
* `generate_random_string()`: Genera una stringa casuale utilizzata come ID univoco.
* `setup_input()`: Genera la mappa input per il menù principale.

***Input***

La classe **`Input`** fornisce una serie di funzioni di supporto per gli input dell'utente, tra cui i metodi di acquisizione, gestione e validazione dell'input utente.

**Funzioni principali:**

* `get_contact_input()`: Acquisisce l'input dell'utente e crea un oggetto Contact*.
* `get_client_input()`: Acquisisce l'input dell'utente e crea un oggetto Client*. Collega un contatto che viene creato per l'occasione.
* `get_interaction_input()`: Acquisisce l'input dell'utente e crea un oggetto Interaction*.
* `get_user_confirm()`: Chiede la conferma dell'utente prima di procedere alle modifiche.
* `get_user_index()`: Acquisisce l'input dell'utente per l'indice, ove serva selezionarlo (ad es. nella modifica dei contatti o delle interazioni).

**Esempio di utilizzo:**

`std::string input = Input::get_user_input("Inserisci il nome del cliente:");`

**Il metodo Main()**

La funzione **`main`** rappresenta il punto di ingresso e il cuore principale del programma. Inizializza il CRM, gestisce il loop principale del programma e permette all'utente di interagire con il software tramite comandi da console.

E' stata prevista la predisposizione a gestire CRM multipli, ciascuno con il proprio set di file. Al momento, la funzione istanzia e usa un solo oggetto `InsuraPro::CRM`.

***Funzionalità:***

* Inizializza una nuova istanza della classe `InsuraPro::CRM`.
* Avvia il loop principale del programma, che attende comandi dall'utente.
* Gestisce i comandi inseriti dall'utente tramite la variabile `cmd`, eseguendo le azioni corrispondenti sul CRM (aggiungi, visualizza, modifica, elimina, ricerca, supporto, chiudi, o rispettivi indici per migliorare la user experience).
* Chiude il programma e salva i dati quando l'utente inserisce il comando "chiudi".

***Esempio di utilizzo del programma***

```
Benvenuto nel sistema CRM avanzato di InsuraPro!

I comandi disponibili sono i seguenti:
1. 'supporto' : mostra l'elenco delle funzioni disponibili.
2. 'aggiunta_cliente' : aggiungi un nuovo cliente nel CRM.
3. 'mostra_clienti' : visualizza l'elenco dei clienti presenti nel CRM.
4. 'modifica_cliente' : modifica i dati di un cliente presente nel CRM.
5. 'elimina_cliente' : elimina un cliente presente nel CRM.
6. 'ricerca_cliente' : ricerca un cliente per il suo contatto.
7. 'aggiunta_interazione' : aggiungi un'interazione ad un cliente presente nel CRM.
8. 'mostra_interazioni' : visualizza l'elenco delle interazioni di un cliente presente nel CRM.
9. 'cerca_interazioni' : cerca un'interazione per tipo o data.
10. 'chiudi' : chiudi il programma.

Cosa vuoi fare? ("supporto" o "1" per mostrare tutte le funzioni): 2

Aggiungi uno o piu' clienti nel CRM.

Inserisci i dati dell'azienda:
Nome Azienda (obbligatorio): Azienda1
Indirizzo Sede: Via di Test, 5
Partita IVA: IT09988776
Email Aziendale: email@azienda.it
Telefono Aziendale (con prefisso): +393475885625

Aggiungi ora il contatto del cliente:
Nome (obbligatorio): Gabriele
Cognome: Scorpaniti
Indirizzo: Via di Test, 4
Email: email@azienda.it
Telefono (con prefisso): +393334455666

Vuoi aggiungere un altro cliente? (si/no): no

Vuoi davvero aggiungere 1 clienti nel CRM? (si/no): si

Clienti aggiunti con successo!

Cosa vuoi fare? ("supporto" o "1" per mostrare tutte le funzioni): 6

Ricerca i clienti del CRM.

Inserisci i parametri di ricerca: Az

Sono stati trovati 3 clienti che corrispondono alla ricerca:

Cliente ID: cli-cvkcxbxmbp. Nome: Azienda1, Indirizzo: , VAT: IT099876859, Email: email@email.it, Telefono: +393556558895
Cliente ID: cli-bvzi9obxvy. Nome: Azienda2, Indirizzo: , VAT: , Email: , Telefono:
Cliente ID: cli-62q1f2hrvr. Nome: Azienda1, Indirizzo: Via di Test, 5, VAT: IT09988776, Email: email@azienda.it, Telefono: +393475885625

Cosa vuoi fare? ("supporto" o "1" per mostrare tutte le funzioni): 7

Aggiungi nuove interazioni nel CRM.

Nome (obbligatorio): Interazione1
Tipo (appuntamento/contratto) - obbligatorio: contratto
Data dell'interazione: 5/06/2024
Descrizione: Il cliente ha acquistato 20 licenze Microsoft
Vuoi aggiungere un'altra interazione? (si/no): no

Ricerca ora il cliente al quale collegare le interazioni inserite.
Inserisci i parametri di ricerca: Az
Clienti trovati:
1. Azienda1
2. Azienda2
3. Azienda1 Via di Test, 5

A quale di questi vuoi associare le interazioni inserite? Inserisci il numero corrispondente: 3


Vuoi davvero aggiungere 1 interazioni nel CRM? (si/no): si

Interazioni aggiunte con successo!

Cosa vuoi fare? ("supporto" o "1" per mostrare tutte le funzioni): 8

Visualizza le interazioni presenti. Ricerca per cliente:

Inserisci i parametri di ricerca: Az
Clienti trovati:
1. Azienda1
2. Azienda2
3. Azienda1 Via di Test, 5

Di quale di questi clienti vuoi visualizzare le interazioni? Inserisci il numero corrispondente: 3

Interazioni del Cliente Azienda1 :

Interazioni trovate: 1

Nome: Interazione1 | Tipo: contratto | Data: 5/06/2024 | Descrizione: Il cliente ha acquistato 20 licenze Microsoft

Cosa vuoi fare? ("supporto" o "1" per mostrare tutte le funzioni): 10
Grazie per aver usato InsuraPro, a presto!
```

**Referenze e bibliografia utilizzata per il progetto**

* **Rapidcsv library:** https://github.com/d99kris/rapidcsv?tab=readme-ov-file#more-examples
* **Gestione delle stringhe in C++:** https://stackoverflow.com/questions/20326356/how-to-remove-all-the-occurrences-of-a-char-in-c-string
* **Gestione delle stringhe random in C++** https://medium.com/@ryan_forrester_/c-random-string-generation-practical-guide-e7e789b348d4

