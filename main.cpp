#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <random>
#include <map>



class Sequence {
protected:
    std::string value;
public:
    Sequence() = default;
    explicit Sequence(const std::string& v) : value(v) {}
    virtual ~Sequence() = default;

    const std::string& get() const { return value; }
    std::size_t length() const { return value.size(); }

    virtual bool is_valid() const = 0;

    virtual void print(const std::string& label) const {
        std::cout << label << ": " << value << " (length=" << length() << ")\n";
    }
};



// DNA: A, C, G, T
class DNASequence : public Sequence {
public:
    DNASequence() = default;
    explicit DNASequence(const std::string& v) : Sequence(v) {}

    bool is_valid() const override {
        if (value.empty()) return false;
        for (char c : value) {
            char u = std::toupper(static_cast<unsigned char>(c));
            if (u != 'A' && u != 'C' && u != 'G' && u != 'T') {
                return false;
            }
        }
        return true;
    }
};



// RNA: A, C, G, U
class RNASequence : public Sequence {
public:
    RNASequence() = default;
    explicit RNASequence(const std::string& v) : Sequence(v) {}

    bool is_valid() const override {
        if (value.empty()) return false;
        for (char c : value) {
            char u = std::toupper(static_cast<unsigned char>(c));
            if (u != 'A' && u != 'C' && u != 'G' && u != 'U') {
                return false;
            }
        }
        return true;
    }
};





// Protein: A,R,N,D,C,Q,E,G,H,I,L,K,M,F,P,S,T,W,Y,V
class ProteinSequence : public Sequence {
public:
    ProteinSequence() = default;
    explicit ProteinSequence(const std::string& v) : Sequence(v) {}

    bool is_valid() const override {
        if (value.empty()) return false;
        const std::string allowed = "ARNDCQEGHILKMFPSTWYV";
        for (char c : value) {
            char u = std::toupper(static_cast<unsigned char>(c));
            if (allowed.find(u) == std::string::npos) {
                return false;
            }
        }
        return true;
    }
};



class Gene {
    DNASequence dna;
public:
    Gene() = default;
    explicit Gene(const DNASequence& d) : dna(d) {}

    const DNASequence& get_dna() const { return dna; }

    // Μεταγραφή DNA -> RNA
    RNASequence transcribe() const {
        std::string rna;
        rna.reserve(dna.get().size());
        for (char c : dna.get()) {
            char u = std::toupper(static_cast<unsigned char>(c));
            switch (u) {
                case 'A': rna.push_back('U'); break;
                case 'T': rna.push_back('A'); break;
                case 'C': rna.push_back('G'); break;
                case 'G': rna.push_back('C'); break;
                default:  rna.push_back('N'); break; // shouldn't happen if DNA valid
            }
        }
        return RNASequence(rna);
    }

    void print(int index) const {
        std::cout << "  Gene " << index << " - ";
        dna.print("DNA");
    }
};




class Ribosome {
    int id;
public:
    explicit Ribosome(int id_) : id(id_) {}

    int get_id() const { return id; }

    ProteinSequence translate(const RNASequence& rna) const {
        static const std::map<std::string, char> codonTable = {
            {"AUG", 'M'},
            {"UUU", 'F'}, {"UUC", 'F'},
            {"UUA", 'L'}, {"UUG", 'L'},
            {"UCU", 'S'}, {"UCC", 'S'}, {"UCA", 'S'}, {"UCG", 'S'},
            {"UAU", 'Y'}, {"UAC", 'Y'},
            {"UGU", 'C'}, {"UGC", 'C'},
            {"UGG", 'W'},
            {"CUU", 'L'}, {"CUC", 'L'}, {"CUA", 'L'}, {"CUG", 'L'},
            {"CCU", 'P'}, {"CCC", 'P'}, {"CCA", 'P'}, {"CCG", 'P'},
            {"CAU", 'H'}, {"CAC", 'H'},
            {"CAA", 'Q'}, {"CAG", 'Q'},
            {"CGU", 'R'}, {"CGC", 'R'}, {"CGA", 'R'}, {"CGG", 'R'},
            {"AUU", 'I'}, {"AUC", 'I'}, {"AUA", 'I'},
            {"ACU", 'T'}, {"ACC", 'T'}, {"ACA", 'T'}, {"ACG", 'T'},
            {"AAU", 'N'}, {"AAC", 'N'},
            {"AAA", 'K'}, {"AAG", 'K'},
            {"AGU", 'S'}, {"AGC", 'S'},
            {"AGA", 'R'}, {"AGG", 'R'},
            {"GUU", 'V'}, {"GUC", 'V'}, {"GUA", 'V'}, {"GUG", 'V'},
            {"GCU", 'A'}, {"GCC", 'A'}, {"GCA", 'A'}, {"GCG", 'A'},
            {"GAU", 'D'}, {"GAC", 'D'},
            {"GAA", 'E'}, {"GAG", 'E'},
            {"GGU", 'G'}, {"GGC", 'G'}, {"GGA", 'G'}, {"GGG", 'G'}
        };

        std::string protein;
        const std::string& s = rna.get();
        std::size_t n = s.size();

        for (std::size_t i = 0; i + 2 < n; i += 3) {
            std::string codon;
            codon.push_back(std::toupper(static_cast<unsigned char>(s[i])));
            codon.push_back(std::toupper(static_cast<unsigned char>(s[i+1])));
            codon.push_back(std::toupper(static_cast<unsigned char>(s[i+2])));
            auto it = codonTable.find(codon);
            if (it != codonTable.end()) {
                protein.push_back(it->second);
            } else {
                protein.push_back('X'); 
            }
        }
        return ProteinSequence(protein);
    }

    void print() const {
        std::cout << "  Ribosome " << id << "\n";
    }
};




class Nucleus {
    std::vector<Gene> genes;
public:
    Nucleus() {
        std::cout << "A nucleus was just constructed!\n";
    }
    ~Nucleus() {
        std::cout << "A nucleus is being destroyed!\n";
    }

    void add_gene(const Gene& g) {
        genes.push_back(g);
    }

    std::vector<RNASequence> transcription() const {
        std::cout << "Nucleus: starting transcription of " << genes.size() << " genes.\n";
        std::vector<RNASequence> rnas;
        rnas.reserve(genes.size());
        int idx = 0;
        for (const auto& g : genes) {
            auto rna = g.transcribe();
            std::cout << "  Gene " << idx++ << " transcribed to RNA: " << rna.get() << "\n";
            rnas.push_back(rna);
        }
        return rnas;
    }

    void print() const {
        std::cout << "Nucleus:\n";
        int idx = 0;
        for (const auto& g : genes) {
            g.print(idx++);
        }
    }
};




class Cytoplasm {
    std::vector<Ribosome> ribosomes;
public:
    Cytoplasm() {
        std::cout << "A cytoplasm was just constructed!\n";
    }
    ~Cytoplasm() {
        std::cout << "A cytoplasm is being destroyed!\n";
    }

    void init_ribosomes(int L) {
        ribosomes.clear();
        for (int i = 0; i < L; ++i) {
            ribosomes.emplace_back(i);
        }
    }

    std::vector<Ribosome>& get_ribosomes() { return ribosomes; }
    const std::vector<Ribosome>& get_ribosomes() const { return ribosomes; }

    void print() const {
        std::cout << "Cytoplasm with " << ribosomes.size() << " ribosomes.\n";
        for (const auto& r : ribosomes) {
            r.print();
        }
    }
};




class EndoplasmicReticulum {
public:
    EndoplasmicReticulum() {
        std::cout << "An endoplasmic reticulum was just constructed!\n";
    }
    ~EndoplasmicReticulum() {
        std::cout << "An endoplasmic reticulum is being destroyed!\n";
    }

    void transition(const std::vector<RNASequence>& rnas,
                    std::vector<Ribosome>& ribosomes,
                    std::vector<ProteinSequence>& proteins,
                    std::mt19937& rng) const {
        if (ribosomes.empty()) return;
        std::uniform_int_distribution<> dist(0, static_cast<int>(ribosomes.size()) - 1);
        int idx = 0;
        for (const auto& rna : rnas) {
            int ribIndex = dist(rng);
            std::cout << "ER: sending RNA " << idx++ << " to ribosome " << ribIndex << "\n";
            ProteinSequence protein = ribosomes[ribIndex].translate(rna);
            proteins.push_back(protein);
        }
    }
};




class Cell {
    Nucleus nucleus;
    Cytoplasm cytoplasm;
    EndoplasmicReticulum er;

    std::vector<RNASequence> produced_rnas;
    std::vector<ProteinSequence> produced_proteins;

public:
    Cell(const std::vector<DNASequence>& dnaSeqs, int L) {
        std::cout << "A cell was just constructed!\n";
        for (const auto& dna : dnaSeqs) {
            nucleus.add_gene(Gene(dna));
        }
        cytoplasm.init_ribosomes(L);
    }

    ~Cell() {
        std::cout << "A cell is being destroyed!\n";
    }

    void protein_synthesis(std::mt19937& rng) {
        produced_rnas = nucleus.transcription();
        produced_proteins.clear();
        er.transition(produced_rnas, cytoplasm.get_ribosomes(), produced_proteins, rng);
    }

    void print() const {
        std::cout << "===== Cell =====\n";
        nucleus.print();

        std::cout << "RNA sequences produced (" << produced_rnas.size() << "):\n";
        int idx = 0;
        for (const auto& rna : produced_rnas) {
            std::cout << "  RNA " << idx++ << " - ";
            rna.print("RNA");
        }

        cytoplasm.print();

        std::cout << "Proteins produced (" << produced_proteins.size() << "):\n";
        idx = 0;
        for (const auto& prot : produced_proteins) {
            std::cout << "  Protein " << idx++ << " - ";
            prot.print("Protein");
        }
        std::cout << "================\n";
    }

    const std::vector<RNASequence>& get_rnas() const { return produced_rnas; }
    const std::vector<ProteinSequence>& get_proteins() const { return produced_proteins; }
};

bool parse_int(const char* s, int& out) {
    try {
        out = std::stoi(s);
        return true;
    } catch (...) {
        return false;
    }
}




                        //-- MAIN FUNCTION --//

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " K L M\n";
        return 1;
    }

    int K, L, M;
    if (!parse_int(argv[1], K) || !parse_int(argv[2], L) || !parse_int(argv[3], M) ||
        K <= 0 || L <= 0 || M <= 0) {
        std::cerr << "Invalid K, L or M. They must be positive integers.\n";
        return 1;
    }

    std::random_device rd;
    std::mt19937 rng(rd());

    for (int cycle = 1; cycle <= M; ++cycle) {
        std::cout << "\n=== Cycle " << cycle << " ===\n";
        std::vector<DNASequence> validDNA;
        validDNA.reserve(K);

        while (static_cast<int>(validDNA.size()) < K) {
            std::string line;
            std::cout << "Enter DNA sequence (" << validDNA.size() << "/" << K << " valid so far): ";
            if (!std::getline(std::cin, line)) {
                std::cerr << "Input error.\n";
                return 1;
            }
            if (line.empty()) {
                continue;
            }
            DNASequence dna(line);
            if (!dna.is_valid()) {
                std::cout << "  Invalid DNA sequence, discarded.\n";
            } else {
                std::cout << "  Valid DNA sequence accepted.\n";
                validDNA.push_back(dna);
            }
        }
        {
            Cell cell(validDNA, L);
      
            cell.protein_synthesis(rng);
          
            cell.print();

            std::cout << "Validity check for produced RNA:\n";
            int idx = 0;
            for (const auto& rna : cell.get_rnas()) {
                std::cout << "  RNA " << idx << " is " << (rna.is_valid() ? "valid" : "INVALID") << "\n";
                ++idx;
            }

            std::cout << "Validity check for produced proteins:\n";
            idx = 0;
            for (const auto& prot : cell.get_proteins()) {
                std::cout << "  Protein " << idx << " is " << (prot.is_valid() ? "valid" : "INVALID") << "\n";
                ++idx;
            }
        }

        std::cout << "=== End of cycle " << cycle << " ===\n";
    }
 return 0;
}
