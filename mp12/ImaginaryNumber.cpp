#include "ImaginaryNumber.h"
#include "helper.h"

ImaginaryNumber::ImaginaryNumber()
{
    /* Your code here */
    number_type = IMAGINARY;
    magnitude = 0;
    phase = calculate_phase(0,0);
    imaginary_component = 0;
}

ImaginaryNumber::ImaginaryNumber(double rval)
{
    /* Your code here */
    number_type = IMAGINARY;
    magnitude = abs(rval);
    phase = calculate_phase(0,rval);
    imaginary_component = rval;
}

ImaginaryNumber::ImaginaryNumber( const ImaginaryNumber& other )
{
    /* Your code here */
    number_type = other.get_number_type();
    magnitude = other.get_magnitude();
    phase = other.get_phase();
    imaginary_component = other.get_imaginary_component();
}

void ImaginaryNumber::set_imaginary_component (double rval)
{
    /* Your code here */
    magnitude = abs(rval);
    phase = calculate_phase(0,rval);
    imaginary_component = rval;
}

double ImaginaryNumber::get_imaginary_component() const
{
    /* Your code here */
    return imaginary_component;
}

//Getter function for magnitude
double ImaginaryNumber::get_magnitude() const{
    /* Your code here */
    return magnitude;
}

//Getter function for phase
double ImaginaryNumber::get_phase() const{
    /* Your code here */
    return phase;
}



//Operator Overload
ImaginaryNumber ImaginaryNumber::operator + (const ImaginaryNumber& arg)
{
    /* Your code here */
    return ImaginaryNumber(imaginary_component + arg.get_imaginary_component());
}

ImaginaryNumber ImaginaryNumber::operator - (const ImaginaryNumber& arg)
{
    /* Your code here */
    return ImaginaryNumber(imaginary_component - arg.get_imaginary_component());
}

RealNumber ImaginaryNumber::operator * (const ImaginaryNumber& arg)
{
    /* Your code here */
    return RealNumber(-1*imaginary_component * arg.get_imaginary_component());
}

RealNumber ImaginaryNumber::operator / (const ImaginaryNumber& arg)
{
    /* Your code here */
    return RealNumber(imaginary_component / arg.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator + (const RealNumber& arg)
{
    /* Your code here */
    return ComplexNumber(arg.get_real_component(), imaginary_component);
}

ComplexNumber ImaginaryNumber::operator - (const RealNumber& arg)
{
    /* Your code here */
    return ComplexNumber(-1*arg.get_real_component(), imaginary_component);
}

ImaginaryNumber ImaginaryNumber::operator * (const RealNumber& arg)
{
    /* Your code here */
    return ImaginaryNumber(imaginary_component*arg.get_real_component());
}

ImaginaryNumber ImaginaryNumber::operator / (const RealNumber& arg)
{
    /* Your code here */
    return ImaginaryNumber(imaginary_component/arg.get_real_component());
}

ComplexNumber ImaginaryNumber::operator + (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber(arg.get_real_component(), imaginary_component + arg.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator - (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber(-1*arg.get_real_component(), imaginary_component - arg.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator * (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber(-1*imaginary_component*arg.get_imaginary_component(), imaginary_component*arg.get_real_component());
}

ComplexNumber ImaginaryNumber::operator / (const ComplexNumber& arg)
{
    /* Your code here */
    double x = arg.get_real_component()*arg.get_real_component() + arg.get_imaginary_component()*arg.get_imaginary_component();
    return ComplexNumber(imaginary_component*arg.get_imaginary_component()/x, imaginary_component*arg.get_real_component()/x);
}

string ImaginaryNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << imaginary_component << 'i';
    return my_output.str();
}