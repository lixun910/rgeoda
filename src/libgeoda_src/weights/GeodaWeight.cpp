#include "GeodaWeight.h"

GeoDaWeight::GeoDaWeight(const GeoDaWeight& gw)
{
	GeoDaWeight::operator=(gw);
}

const GeoDaWeight& GeoDaWeight::operator=(const GeoDaWeight& gw)
{
	weight_type = gw.weight_type;
	wflnm = gw.wflnm;
	title = gw.title;
	symmetry_checked = gw.symmetry_checked;
	is_symmetric = gw.is_symmetric;
	num_obs = gw.num_obs;
	
	return *this;
}

std::string GeoDaWeight::GetTitle()  const
{
	return title;
}

double GeoDaWeight::GetSparsity() const
{
    return sparsity;
}
double GeoDaWeight::GetDensity() const
{
    return density;
}
int GeoDaWeight::GetNumObs() const
{
    return num_obs;
}

int GeoDaWeight::GetMinNumNbrs() const
{
    return min_nbrs;
}
int GeoDaWeight::GetMaxNumNbrs() const
{
    return max_nbrs;
}
double GeoDaWeight::GetMeanNumNbrs() const
{
    return mean_nbrs;
}
double GeoDaWeight::GetMedianNumNbrs() const
{
    return median_nbrs;
}