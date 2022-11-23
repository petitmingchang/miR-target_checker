#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int num_of_miRNA;
int num_of_Target;
int num_of_Pair; 

typedef struct Name_List {
    char name[20];
    //char gene_ID[20];
    //int *CM_exp;
}Name_List;

typedef struct Pair {
    char miR_name[40];
    char gene_name[40];
    //char cluster_ligand[20];
    //char cluster_receptor[20];
    //int cluster_ID;
    int hit_miR;
    int hit_gene;
}Pair;

Name_List *miRNA_table;
Name_List *Target_table;
Pair *Pair_table;

void Read_miRNA (char *input) {

	FILE *fptr = fopen(input, "r");
	char miRNA_Name[20];

	num_of_miRNA = 0;
	
	while(fscanf(fptr, "%s", miRNA_Name) != EOF) {
		num_of_miRNA++;
    }
	
	rewind(fptr);
    //table initialization
    miRNA_table = new Name_List[num_of_miRNA];
    //for (int i=0; i<num_of_miRNA; i++) {
	//	strcpy(miRNA_table[i], '\0');
    //}
    
    //Read file to tables
    int index = 0;
	while(fscanf(fptr, "%s", miRNA_Name) != EOF) {
		strcpy(miRNA_table[index].name, miRNA_Name);
		index++;
	}
	
	fclose(fptr);
}

void Read_Target (char *input) {

	FILE *fptr = fopen(input, "r");
	char Target_Name[20];

	num_of_Target = 0;
	
	while(fscanf(fptr,"%s", Target_Name) != EOF) {
		num_of_Target++;
    }
	
	rewind(fptr);
    //table initialization
    Target_table = new Name_List[num_of_Target];
    //for (int i=0; i<num_of_Target; i++) {
	//	strcpy(Target_table[i], '\0');
    //}
    
    //Read file to tables
    int index = 0;
	while(fscanf(fptr,"%s", Target_Name) != EOF) {
		strcpy(Target_table[index].name, Target_Name);
		index++;
	}
	
	fclose(fptr);
}

void Read_pair_DB (char *input) {
    FILE *fptr = fopen(input, "r");
    char microRNA_name[40];
    char target_gene_name[40];
    
    //printf("Reading known_miRNA-target pairs ......");
    
    num_of_Pair = 0;
    while(fscanf(fptr,"%s\t%s", microRNA_name, target_gene_name) != EOF) {
        num_of_Pair++;
    }
    
    rewind(fptr);
    //table initialization
    Pair_table = new Pair[num_of_Pair];

    int index = 0;
    while(fscanf(fptr,"%s\t%s", microRNA_name, target_gene_name) != EOF) {
        strcpy(Pair_table[index].miR_name, microRNA_name);
        strcpy(Pair_table[index].gene_name, target_gene_name);
        Pair_table[index].hit_miR = 0;
        Pair_table[index].hit_gene = 0;
        index++;
    }
    
    fclose(fptr);
    //printf(" ...done\n");
}


void check_pair() {

	for (int i=0; i<num_of_miRNA; i++) {
		for (int k=0; k<num_of_Pair; k++) {
			if (strcmp(miRNA_table[i].name, Pair_table[k].miR_name) == 0) {
				Pair_table[k].hit_miR = 1;
			}
		}
	}
	
	for (int j=0; j<num_of_Target; j++) {
		for (int k=0; k<num_of_Pair; k++) {
			if (strcmp(Target_table[j].name, Pair_table[k].gene_name) ==0) {
				Pair_table[k].hit_gene = 1;
			}
		}
	}

}

void output () {

	FILE *fout1;
	fout1 = fopen("matched_pairs.tsv","w");

	int index = 1;
	fprintf(fout1,"s.no\tmicroRNA\ttarget gene\n");
	for (int i=0; i<num_of_Pair; i++) {
		if( (Pair_table[i].hit_miR + Pair_table[i].hit_gene) == 2) {
			fprintf(fout1, "%d\t%s\t%s\n", index++, Pair_table[i].miR_name, Pair_table[i].gene_name);
		}
	}
	fclose(fout1);
}

int main(int argc, char* argv[]) {
    char input_file1[100];   //miRNA list
    char input_file2[100];   //target gene list
    char input_file3[100];   //miRNA-target pair from database

    if (argc != 4) {
        printf("\nUsage: miRNA-target_pairing miRNA_list target_list miRNA-target_pair_DB\n");
    } else {
        
        strcpy(input_file1, argv[1]);
        strcpy(input_file2, argv[2]);
        strcpy(input_file3, argv[3]);
    
        FILE *fptr1 = fopen(input_file1, "r");
        FILE *fptr2 = fopen(input_file2, "r");
        FILE *fptr3 = fopen(input_file3, "r");
        
        if(fptr1 == NULL || fptr2 == NULL || fptr3 == NULL) {
            
            printf("\nCan't find the input file. Please check the inupt file again!\n\n");
            
        } else {
    
            fclose (fptr1);
            fclose (fptr2);
            fclose (fptr3);
            
            printf("Checking microRNA -> target gene pairs in %s ......", input_file3);
    
            Read_miRNA(input_file1);
            Read_Target(input_file2);
            Read_pair_DB(input_file3);
            
            check_pair();
            output();
            
            printf(" done\n");
        }
    }
    
    return 0;

}

