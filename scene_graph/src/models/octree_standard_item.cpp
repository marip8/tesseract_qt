/**
 * @author Levi Armstrong <levi.armstrong@gmail.com>
 *
 * @copyright Copyright (C) 2022 Levi Armstrong <levi.armstrong@gmail.com>
 *
 * @par License
 * GNU Lesser General Public License Version 3, 29 June 2007
 * @par
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 * @par
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * @par
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#include <tesseract_qt/scene_graph/models/octree_standard_item.h>
#include <tesseract_qt/common/models/standard_item_utils.h>
#include <tesseract_qt/common/models/standard_item_type.h>
#include <tesseract_qt/common/icon_utils.h>

namespace tesseract_gui
{
OctreeStandardItem::OctreeStandardItem(tesseract_geometry::Octree::ConstPtr octree)
  : QStandardItem(icons::getOctreeIcon(), "Octree"), octree(std::move(octree))
{
  ctor();
}

OctreeStandardItem::OctreeStandardItem(const QString& text, tesseract_geometry::Octree::ConstPtr octree)
  : QStandardItem(icons::getOctreeIcon(), text), octree(std::move(octree))
{
  ctor();
}

OctreeStandardItem::OctreeStandardItem(const QIcon& icon,
                                       const QString& text,
                                       tesseract_geometry::Octree::ConstPtr octree)
  : QStandardItem(icon, text), octree(std::move(octree))
{
  ctor();
}

int OctreeStandardItem::type() const { return static_cast<int>(StandardItemType::SG_OCTREE); }

void OctreeStandardItem::ctor()
{
  appendRow(createStandardItemString("pruned", (octree->getPruned()) ? "True" : "False"));

  switch (octree->getSubType())
  {
    case tesseract_geometry::Octree::BOX:
    {
      appendRow(createStandardItemString(icons::getCubeIcon(), "subshape", "BOX"));
      break;
    }
    case tesseract_geometry::Octree::SPHERE_INSIDE:
    {
      appendRow(createStandardItemString(icons::getSphereIcon(), "subshape", "SPHERE INSIDE"));
      break;
    }
    case tesseract_geometry::Octree::SPHERE_OUTSIDE:
    {
      appendRow(createStandardItemString(icons::getSphereIcon(), "subshape", "SPHERE OUTSIDE"));
      break;
    }
  }

  appendRow(createStandardItemFloat("shape count", octree->calcNumSubShapes()));
}
}  // namespace tesseract_gui
