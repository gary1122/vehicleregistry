#include "vehicleregistry.h"

VehicleRegistry:: VehicleRegistry()
{
	maxsize = 4;
	vehicles = new Vehicle[maxsize];
	numvehicles = 0;
}


VehicleRegistry::~VehicleRegistry()
{
	delete[] vehicles;
}

VehicleRegistry::VehicleRegistry(const VehicleRegistry& vr)
{
	CopyArray(vr);
}

void VehicleRegistry::CopyArray(const VehicleRegistry& vr)
{
	numvehicles = vr.numvehicles;
	maxsize = vr.maxsize;
	vehicles = new Vehicle[maxsize];
	for(int i =0; i < numvehicles; i++)
	{
	vehicles[i] = vr.vehicles[i];
	}
}


bool VehicleRegistry::Insert(Vehicle vehicle)
{
	for (int i = 0; i < numvehicles;i++)
	{
		if (vehicle.GetPlate() == vehicles[i].GetPlate())
		{
			return false;
		}
	}
	 
	if (numvehicles < maxsize)
	{
		vehicles[numvehicles++] = vehicle;
		return true;
	}
	else 
	{
		Vehicle* temp = vehicles;
		maxsize = 2*maxsize;
		vehicles = new Vehicle[maxsize];
		for (int i = 0; i < numvehicles; i++)
		{
			vehicles[i] = temp[i];
		}
		delete[] temp;
		vehicles[numvehicles++] = vehicle;
		return true;
	}
	return false;
}

bool VehicleRegistry::Remove(Vehicle vehicle)
{
	for (int i = 0; i< numvehicles; i++)
	{
		if ( vehicle.GetColour() == vehicles[i].GetColour() && vehicle.GetMake() == vehicles[i].GetMake()&& vehicle.GetModel() == vehicles[i].GetModel() && vehicle.GetPlate() == vehicles[i].GetPlate())
		{
			vehicles[i] = vehicles[numvehicles-1];
			numvehicles--;
			return true;
		}
	}

	return false;
}


int VehicleRegistry::Find(Vehicle vehicle) const
{
		for (int i = 0; i< numvehicles; i++)
	{
		if ( vehicle.GetColour() == vehicles[i].GetColour() && vehicle.GetMake() == vehicles[i].GetMake()&& vehicle.GetModel() == vehicles[i].GetModel() && vehicle.GetPlate() == vehicles[i].GetPlate())
		{
			
			return i;
		}
	}

	return -1;
}


VehicleRegistry VehicleRegistry::Join(const VehicleRegistry& vr) const
{
	VehicleRegistry JoinRegistry;
	for(int i = 0; i < numvehicles; i++)
	{
		JoinRegistry.Insert(vehicles[i]);
	}

	for(int k = 0; k < vr.numvehicles; k++)
	{
		JoinRegistry.Insert(vr.vehicles[k]);
	}


	return JoinRegistry;
}

VehicleRegistry VehicleRegistry::Common(const VehicleRegistry& vr) const
{
	VehicleRegistry CommonRegistry;
	for(int i = 0; i < numvehicles; i++)
	{
		for(int k = 0; k < vr.numvehicles; k++)
		{
			if (vehicles[i].GetPlate() == vr.vehicles[i].GetPlate())
			{
				CommonRegistry.Insert(vehicles[i]);
			}
		}
	}


	return CommonRegistry;;
}

VehicleRegistry VehicleRegistry::Split(const VehicleRegistry& vr) const
{
	VehicleRegistry SplitRegistry;
	for(int i = 0; i < numvehicles; i++)
	{
		SplitRegistry.Insert(vehicles[i]);
	}
	for(int k = 0; k< vr.numvehicles; k++)
	{
		SplitRegistry.Remove(vr.vehicles[k]);
	}


	return SplitRegistry;
}


int VehicleRegistry::Count() const
{
	return numvehicles;
}


