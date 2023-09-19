#include <Impl.hpp>

Impl::Impl(int n){
    this->Num = n;
    this->Ind = Count(n);
    this->P = 0;
    this->Pw = 0;
    this->Inf = 1;
}

Impl::Impl(bool valid){
    if (!valid){
        this->Inf = false;
        this->Num = -1;
        this->P = -1;
        this->Pw = -1;
        this->Ind = -1;
    }
}

int Impl::Count(int n){
    int count = 0;
    while (n > 0){
        if (n % 2 == 1){
            count ++;
        }
        n /= 2;
    }

    return count;
}

bool Impl::isValid() const{
    return this->Inf;
}

void Impl::setPw(){
    this->Pw = true;
}

Impl Impl::Patch(Impl *first, Impl *second){
    if((*first).Num < (*second).Num 
        && (*first).P == (*second).P 
        && (*second).Ind - (*first).Ind == 1
        && Impl::Count((*second).Num - (*first).Num) == 1){

            Impl newImpl = Impl((*first).Num);
            newImpl.P = (*first).P + ((*second).Num - (*first).Num);
            return newImpl;
        } else {
            return Impl{false};
        }
}

bool Impl::operator!= (const Impl& diffImpl) const{
    if ((this->Ind != diffImpl.Ind) 
        || (this->Num != diffImpl.Num)
        || (this->Inf != diffImpl.Inf)
        || (this->P != diffImpl.Inf)
        || (this->Pw != diffImpl.Pw))

        return true;

    else 
        return false;
}

int Impl::GetPw() const{
    return this->Pw;
}

int Impl::GetInd(){
    return this->Ind;
}

int Impl::GetNum() const{
    return this->Num;
}

int Impl::GetP() const{
    return this->P;
}

Impl::~Impl()= default;