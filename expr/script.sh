wget ftp://ftp.1000genomes.ebi.ac.uk/vol1/ftp/data_collections/1000_genomes_project/release/20190312_biallelic_SNV_and_INDEL/ALL.chr22.shapeit2_integrated_snvindels_v2a_27022019.GRCh38.phased.vcf.gz -O chr22.GRCh38.vcf.gz
wget ftp://ftp.1000genomes.ebi.ac.uk/vol1/ftp/technical/reference/GRCh38_reference_genome/GRCh38_full_analysis_set_plus_decoy_hla.fa -O GRCh38.fa
wget https://github.com/vgteam/vg/releases/download/v1.43.0/vg
chmod 755 vg
time ../extract-seq 22 < GRCh38.fa > chr22.GRCh38.fa
time ./vg construct -r chr22.GRCh38.fa -v <(gunzip -c chr22.GRCh38.vcf.gz) > chr22.GRCh38.vg
time ./vg view chr22.GRCh38.vg | ../convert-to-edgelist > chr22.GRCh38.edgelist
time ../nfa2dfa < chr22.GRCh38.edgelist > chr22.GRCh38.dfa
time ../convert-format < chr22.GRCh38.dfa > chr22.GRCh38.inp
time ../graph-sort < chr22.GRCh38.inp > chr22.GRCh38.interval
time ../interval-graph-coloring < chr22.GRCh38.interval > chr22.GRCh38.color
