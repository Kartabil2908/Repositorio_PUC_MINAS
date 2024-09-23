
import java.util.*;


class tp02
{
    class pokemon
    {   
        // VALORES

        private int id;
        private int generation;
        private String name = "";
        private String description = "";
        private List<String> types;
        private List<String> abilities;
        private double weight;
        private double height;
        private int captureRate;
        private boolean isLegendary;
        private Date captureDate;


        // CONSTRUTORES

        pokemon(int id, int gen, String name, String description, List<String> tipos, List<String> habilidades,double peso, double altura,int captura, boolean lendario, Date data)
        {
            this.id = id;
            this.generation = gen;
            this.name = name;
            this.description = description;
            this.types = tipos;
            this.abilities = habilidades;
            this.weight = peso;
            this.height = altura;
            this.captureRate = captura;
            this.isLegendary = lendario;
            this.captureDate = data;


        }

        pokemon()
        {
            this(0,0,"","",null,null,0.0,0.0,0,false,null);
        }

        public int getId() {
            return id;
        }

        public void setId(int id) {
            this.id = id;
        }

        public int getGeneration() {
            return generation;
        }

        public void setGeneration(int generation) {
            this.generation = generation;
        }

        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }

        public String getDescription() {
            return description;
        }

        public void setDescription(String description) {
            this.description = description;
        }

        public List<String> getTypes() {
            return types;
        }

        public void setTypes(List<String> types) {
            this.types = types;
        }

        public List<String> getAbilities() {
            return abilities;
        }

        public void setAbilities(List<String> abilities) {
            this.abilities = abilities;
        }

        public double getWeight() {
            return weight;
        }

        public void setWeight(double weight) {
            this.weight = weight;
        }

        public double getHeight() {
            return height;
        }

        public void setHeight(double height) {
            this.height = height;
        }

        public int getCaptureRate() {
            return captureRate;
        }

        public void setCaptureRate(int captureRate) {
            this.captureRate = captureRate;
        }

        public boolean isLegendary() {
            return isLegendary;
        }

        public void setLegendary(boolean isLegendary) {
            this.isLegendary = isLegendary;
        }

        public Date getCaptureDate() {
            return captureDate;
        }

        public void setCaptureDate(Date captureDate) {
            this.captureDate = captureDate;
        }



    }






}

