#include "voxel_hashing_map.h"

#include <iostream>
#include <optional>

template <class PointT>
void VoxelHashMap<PointT>::insertPoint(const PointT& pt) {
  // Convert to integer leaf.
  IPointXYZ inv_pt{static_cast<int>(pt.x * inverse_leaf_size_),
                   static_cast<int>(pt.y * inverse_leaf_size_),
                   static_cast<int>(pt.z * inverse_leaf_size_)};

  //   std::cout << inv_pt.x << "," << inv_pt.y << "," << inv_pt.z << std::endl;

  if (map_.find(inv_pt) != map_.end()) {
    auto& bucket = map_.at(inv_pt);
    if (bucket.size() < point_bucket_size_) {
      bucket.push_back(pt);
    }
  } else {
    map_[inv_pt].push_back(pt);
  }
}

template <class PointT>
std::optional<const typename VoxelHashMap<PointT>::PointXYZBucket>
VoxelHashMap<PointT>::getBucketAt(const PointT& query_pt) {
  // Convert to integer leaf.
  IPointXYZ inv_pt{static_cast<int>(query_pt.x * inverse_leaf_size_),
                   static_cast<int>(query_pt.y * inverse_leaf_size_),
                   static_cast<int>(query_pt.z * inverse_leaf_size_)};

  if (map_.find(inv_pt) != map_.end())
    return map_.at(inv_pt);
  else
    return std::nullopt;
}

template class VoxelHashMap<pcl::PointXYZ>;