#include "studentc.h"

double Student::Average() const{
    if(scores.size() > 0){
        return scores.sum() / scores.size();
    }
    else return 0;
}

const std::string& Student::Name() const{
    return name;
}

double& Student::operator[](int index){
    return scores[index];
}

double Student::operator[](int index) const{
    return scores[index];
}

std::ostream& Student::arr_out(std::ostream& out) const{
    int lim = scores.size();
    if(lim > 0){
        for(int i=0;i<lim;i++){
            out << scores[i] << " ";
        }
        out << std::endl;
    }
    else out << "Empty array.\n";
    return out;
}

std::istream& operator>>(std::istream& in, Student& src){
    in >> src.name;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Student& src){
    out << "Scores for " << src.name << ":\n";
    src.arr_out(out);
    return out;
}
