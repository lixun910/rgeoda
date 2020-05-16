#ifndef __JSGEODA_GEODA_WEIGHTS_H__
#define __JSGEODA_GEODA_WEIGHTS_H__

#include <string>
#include <vector>

class GeoDaWeight {
public:
	GeoDaWeight() : symmetry_checked(false), num_obs(0) {}
	GeoDaWeight(const GeoDaWeight& gw);
    
	virtual ~GeoDaWeight() {}

    virtual bool   CheckNeighbor(int obs_idx, int nbr_idx) = 0;
    virtual const  std::vector<long> GetNeighbors(int obs_idx) = 0;
    virtual const  std::vector<double> GetNeighborWeights(int obs_idx) = 0;
    virtual void   Update(const std::vector<bool>& undefs) = 0;
    virtual bool   HasIsolates() = 0;
    virtual void   GetNbrStats() = 0;
    
    virtual int    GetNbrSize(int obs_idx) = 0;
    virtual double SpatialLag(int obs_idx,
                              const std::vector<double>& data) = 0;
    virtual bool   Save(const char* ofname,
                              const char* layer_name,
                              const char* id_var_name,
                              const std::vector<int>& id_vec) = 0;

    virtual bool   Save(const char* ofname,
                              const char* layer_name,
                              const char* id_var_name,
                              const std::vector<const char*>& id_vec) = 0;
    // functions:
    virtual double GetSparsity() const;
    virtual double GetDensity() const;
    virtual int    GetMinNumNbrs() const;
    virtual int    GetMaxNumNbrs() const;
    virtual double GetMeanNumNbrs() const;
    virtual double GetMedianNumNbrs() const;
    virtual int    GetNumObs() const;
    virtual bool   IsInternalUse() const { return is_internal_use; }
    
    // Others
    virtual const GeoDaWeight& operator=(const GeoDaWeight& gw);
   
    virtual std::string GetTitle() const; // returns portion of wflnm if title empty
   
    virtual std::string GetIDName() const { return id_field;}

    // Properties
	enum WeightType { gal_type, gwt_type };
	WeightType    weight_type;
	std::string   wflnm; // filename
    std::string   id_field;
	std::string   title; // optional title.  Use wflnm if empty
	bool          symmetry_checked; // indicates validity of is_symmetric bool
	bool          is_symmetric; // true iff matrix is symmetric
	int           num_obs;
    double        sparsity;
    double        density;
    int        min_nbrs;
    int        max_nbrs;
    double     mean_nbrs;
    double     median_nbrs;
    bool       is_internal_use; // if internally used weights structure, will not be shown and used by users
    std::string uid;
};

#endif

