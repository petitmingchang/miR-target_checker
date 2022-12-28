# miR-target_checker
Using user defined lists of up-reguated differentially expressed (DE) microRNA and down-regulated DE gene or vice versa from transcriptomic data to check known miRNA-target dataset.

### How to run the program
First step is to compile the source code to executive file by C++ compliler 
```sh
g++ miR-target_checker.cpp -o miR-target_checker
```
Before running the program, you have to prepare three files, (1) a list up-regulated DE miRNAs, (2) a list of down-regulated DE genes, (3) and a list of miRNA-target pairs downloaded from the websites (e.g. DIANA-TarBase, mirTarBase, TargtScan, or miRDB). The file format of miRNA or gene lists is very simple that only contains a single column of miRNA IDs or gene IDs, respectively. The miRNA-target_pair list is in tab-separated values (.tsv) file, the first and second column contain miRNA ID and gene ID, respectively. You may also take a look at the example files for the reference.   
Usage: ./miR-target_checker miRNA_list.txt gene_list.txt miRNA-target_pair_list.tsv

```sh
./miR-target_checker miRNA_list.txt target_gene_list.txt ./mouse_miRNA-target_DB/TarBase_v8_mouse.tsv
```
