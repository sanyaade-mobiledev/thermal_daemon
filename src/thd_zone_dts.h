/*
 * thd_zone_dts.h: thermal engine DTS class interface
 *
 * Copyright (C) 2012 Intel Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 or later as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 *
 * Author Name <Srinivas.Pandruvada@linux.intel.com>
 *
 * This interface allows to overide per zone read data from sysfs for buggy BIOS. 
 */

#ifndef THD_ZONE_DTS_H
#define THD_ZONE_DTS_H

#include "thd_zone.h"
#include "thd_cdev_pstates.h"
#include "thd_cdev_tstates.h"
#include "thd_cdev_turbo_states.h"
#include "thd_model.h"
#include "thd_topology.h"
#include <vector>

class cthd_zone_dts: public cthd_zone
{
protected:
	csys_fs dts_sysfs;
	int critical_temp;
	int set_point;
	int prev_set_point;
	int trip_point_cnt;
	unsigned int sensor_mask;

	//cthd_cdev_pstates cdev_pstates;
	cthd_topology topology;

	cthd_model thd_model;
	std::vector <std::string> sensor_sysfs;

	int init();
	int update_trip_points();
	int cpu_to_cdev_index(int _index)
	{
		return (4+_index * 4);
	}

public:
	static const int max_dts_sensors = sizeof(unsigned int) *8;
	static const int def_hystersis = 0;
	static const int def_offset_from_critical = 10000;
	cthd_zone_dts(int count, std::string path);

	virtual int read_trip_points();
	int read_cdev_trip_points();
	void set_temp_sensor_path();
	virtual unsigned int read_zone_temp();
	void update_zone_preference();

};

#endif
