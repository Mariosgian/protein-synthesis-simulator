# Protein Synthesis Simulator

A C++ object-oriented simulation of protein synthesis in a eukaryotic cell.

This project models the biological process where DNA is transcribed into RNA
and then translated into proteins inside a simulated cell environment.

---

# System Overview

The simulated cell consists of three main organelles:

• **Nucleus** – contains `K` genes, each initialized with a DNA sequence  
• **Endoplasmic Reticulum (ER)** – transports RNA molecules  
• **Cytoplasm** – contains `L` ribosomes responsible for protein translation  

---

# Protein Synthesis Process

For each simulation cycle the following steps occur:

### 1. DNA Input
The user enters DNA sequences.

Invalid sequences (characters other than `A, C, G, T`) are rejected.

The program collects at least **K valid DNA sequences**.

---

### 2. Cell Construction

A **Cell** object is created containing:

• A **Nucleus** with `K` genes  
• A **Cytoplasm** with `L` ribosomes  
• An **Endoplasmic Reticulum**

---

### 3. Protein Synthesis

The cell performs:

#### Transcription (DNA → RNA)

Occurs in the nucleus using the mapping rule:

A → U
T → A
C → G
G → C

Each gene produces one RNA sequence.

---

#### RNA Transport

The **Endoplasmic Reticulum** transfers each RNA molecule to a **random ribosome**.

---

#### Translation (RNA → Protein)

Ribosomes translate RNA by reading **codons (triplets of nucleotides)**.

Each codon maps to an **amino acid** using the genetic code table provided in the assignment.

The amino acids form a **protein sequence**.

---

# Program Output

After synthesis the program prints:

• The **nucleus** and its genes (DNA sequences)  
• The **RNA sequences** produced  
• The **ribosomes used**  
• The **proteins generated**, including:
  - protein sequence
  - protein length

---

# Compilation

From inside the `hw_bonus` directory run:

```bash
g++ -std=c++17 -O2 -Wall main.cpp -o protein_sim

Execution

The program requires three command-line parameters:

./protein_sim K L M

Where:

Parameter
Description
K
number of genes per cell
L
number of ribosomes
M
number of simulation cycles

Example

./protein_sim 3 2 1


The program will:
	1.	Ask for DNA sequences until 3 valid ones are entered
	2.	Construct a cell with 3 genes and 2 ribosomes
	3.	Perform protein synthesis
	4.	Print the DNA, RNA and proteins produced

⸻

Technologies
	•	C++
	•	Object Oriented Programming
	•	Biological process simulation
