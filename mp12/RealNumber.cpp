#include "RealNumber.h"
#include "helper.h"

RealNumber::RealNumber()
{
    /* Your code here */
    number_type = REAL;
    magnitude = 0;
    phase = calculate_phase(0,0);
    real_component = 0;
}

RealNumber::RealNumber(double rval)
{
    /* Your code here */
    number_type = REAL;
    magnitude = abs(rval);
    phase = calculate_phase(rval, 0);
    real_component = rval;
}

RealNumber::RealNumber( const RealNumber& other )
{
    number_type = other.get_number_type();
    magnitude = other.get_magnitude();
    phase = other.get_phase();
    real_component = other.get_real_component();
}

void RealNumber::set_real_component (double rval)
{
    /* Your code here */
    magnitude = abs(rval);
    phase = calculate_phase(rval,0);
    real_component = rval;
}



double RealNumber::get_real_component() const
{
    /* Your code here */
    return real_component;
}

double RealNumber::get_magnitude() const{
    /* Your code here */
    return magnitude;
}

double RealNumber::get_phase() const{
    /* Your code here */
    return phase;
}

RealNumber RealNumber::operator + (const RealNumber& arg)
{
    /* Your code here */
    return RealNumber(real_component + arg.get_real_component());
}

RealNumber RealNumber::operator - (const RealNumber& arg)
{
    /* Your code here */
    return RealNumber(real_component - arg.get_real_component());
}

RealNumber RealNumber::operator * (const RealNumber& arg)
{
    /* Your code here */
    return RealNumber(real_component * arg.get_real_component());
}

RealNumber RealNumber::operator / (const RealNumber& arg)
{
    /* Your code here */
    return RealNumber(real_component / arg.get_real_component()
);
}

ComplexNumber RealNumber::operator + (const ImaginaryNumber& arg){
    /* Your code here */
	return ComplexNumber(real_component, arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator - (const ImaginaryNumber& arg){
    /* Your code here */
	return ComplexNumber(real_component, -1*arg.get_imaginary_component());
}

ImaginaryNumber RealNumber::operator * (const ImaginaryNumber& arg){
    /* Your code here */
	return ImaginaryNumber(real_component*arg.get_imaginary_component());
}

ImaginaryNumber RealNumber::operator / (const ImaginaryNumber& arg){
    /* Your code here */
	return ImaginaryNumber((-1*real_component)/arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator + (const ComplexNumber& arg){
    /* Your code here */
    return ComplexNumber(real_component + arg.get_real_component(), arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator - (const ComplexNumber& arg){
    /* Your code here */
    return ComplexNumber(real_component - arg.get_real_component(), -1*arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator * (const ComplexNumber& arg){
    /* Your code here */
	return ComplexNumber(real_component*arg.get_real_component(), real_component*arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator / (const ComplexNumber& arg){
    /* Your code here */
    double x= arg.get_real_component()*arg.get_real_component()+arg.get_imaginary_component()*arg.get_imaginary_component();
    return ComplexNumber(real_component*arg.get_real_component()/x, real_component*arg.get_imaginary_component()/x);
}

string RealNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << real_component;
    return my_output.str();
}