# <b> Bonus Assignment </b>

<br>

## Description

This program simulates, in a simplified way, the process of protein synthesis in a eukaryotic cell using C++.

The cell consists of three main organelles:
- Nucleus – contains `K` genes, each with a DNA sequence.
- Endoplasmic Reticulum (ER) – transfers RNA molecules to ribosomes.
- Cytoplasm – contains `L` ribosomes.

For each simulation cycle:

1. The user enters DNA sequences.

2. Invalid DNA sequences (characters other than A, C, G, T) are rejected.

3. When `K` valid DNA sequences have been collected, a Cell is created:
   - The Nucleus stores `K` genes (each with one DNA sequence).
   - The Cytoplasm contains `L` ribosomes.

4. The cell performs protein_synthesis:
   - Transcription (in the nucleus): DNA → RNA using the rule A→U, T→A, C→G, G→C.
   - Transition (via ER): each RNA is sent to a random ribosome.
   - Translation (in ribosomes): RNA → Protein by reading codons (triplets of RNA) and mapping them to amino acids using the genetic code table from the assignment.

5. The program prints:
   - The nucleus and its genes (DNA),
   - The RNA sequences produced,
   - The ribosomes,
   - The proteins produced (with their sequences and lengths).

<br>

## How to compile 

From inside the `hw_bonus` directory run:

    g++ -std=c++17 -O2 -Wall main.cpp -o protein_sim


## How to run

The program takes three command-line arguments:

    ./protein_sim K L M

Where:
- `K` = number of genes (valid DNA sequences) per cell
- `L` = number of ribosomes in the cytoplasm
- `M` = number of simulation cycles

Example:

    ./protein_sim 3 2 1

In this example, the program will:
- Ask for DNA sequences until it collects 3 valid ones,
- Create a cell with 3 genes and 2 ribosomes,
- Perform protein synthesis (transcription, transition, translation),
- Print the DNA of each gene, the RNA sequences, the ribosomes, and the proteins produced.
