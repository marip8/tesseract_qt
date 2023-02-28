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
#ifndef TESSERACT_QT_COMMON_CONTACT_RESULTS_EVENTS_H
#define TESSERACT_QT_COMMON_CONTACT_RESULTS_EVENTS_H

#include <memory>
#include <tesseract_qt/common/events/event_type.h>
#include <tesseract_qt/common/events/component_events.h>
#include <tesseract_qt/common/contact_results_types.h>

namespace tesseract_scene_graph
{
class SceneState;
}

namespace tesseract_gui::events
{
class ContactResultsClear : public ComponentEvent
{
public:
  ContactResultsClear(ComponentInfo component_info, const std::string& ns = "");
  ~ContactResultsClear() override;

  const std::string& getNamespace() const;

  /** @brief Unique type for this event. */
  static const QEvent::Type kType = QEvent::Type(EventType::CONTACT_RESULTS_CLEAR);

private:
  std::string ns_;
};

class ContactResultsSet : public ComponentEvent
{
public:
  ContactResultsSet(ComponentInfo component_info,
                    const std::variant<ContactResultVector, ContactResultMap>& contact_results,
                    const std::string& ns = "");
  ~ContactResultsSet() override;

  const std::string& getNamespace() const;
  const std::variant<ContactResultVector, ContactResultMap>& getContactResults() const;

  /** @brief Unique type for this event. */
  static const QEvent::Type kType = QEvent::Type(EventType::CONTACT_RESULTS_SET);

private:
  std::string ns_;
  std::variant<ContactResultVector, ContactResultMap> contact_results_;
};

class ContactResultsRemove : public ComponentEventUUID
{
public:
  ContactResultsRemove(ComponentInfo component_info, boost::uuids::uuid uuid);
  ContactResultsRemove(ComponentInfo component_info, boost::uuids::uuid uuid, boost::uuids::uuid child_uuid);
  ~ContactResultsRemove() override;

  /** @brief Unique type for this event. */
  static const QEvent::Type kType = QEvent::Type(EventType::CONTACT_RESULTS_REMOVE);
};

class ContactResultsVisbility : public ComponentEventVisibility
{
public:
  ContactResultsVisbility(ComponentInfo component_info, boost::uuids::uuid uuid, bool visible);
  ContactResultsVisbility(ComponentInfo component_info,
                          boost::uuids::uuid uuid,
                          boost::uuids::uuid child_uuid,
                          bool visible);
  ~ContactResultsVisbility() override;

  /** @brief Unique type for this event. */
  static const QEvent::Type kType = QEvent::Type(EventType::CONTACT_RESULTS_VISIBILITY);
};

class ContactResultsVisbilityAll : public ComponentEventVisibilityAll
{
public:
  ContactResultsVisbilityAll(ComponentInfo component_info, bool visible);
  ~ContactResultsVisbilityAll() override;

  /** @brief Unique type for this event. */
  static const QEvent::Type kType = QEvent::Type(EventType::CONTACT_RESULTS_VISIBILITY_ALL);
};

class ContactResultsCompute : public ComponentEvent
{
public:
  enum StateType
  {
    CURRENT_STATE,
    NAMED_STATE,
    USER_DEFINED_STATE
  };

  ContactResultsCompute(ComponentInfo component_info,
                        tesseract_collision::CollisionCheckConfig config,
                        StateType state_type = CURRENT_STATE,
                        std::string ns = "");
  ~ContactResultsCompute() override;

  const std::string& getNamespace() const;
  const tesseract_collision::CollisionCheckConfig& getConfig() const;
  StateType getStateType() const;

  /** @brief Unique type for this event. */
  static const QEvent::Type kType = QEvent::Type(EventType::CONTACT_RESULTS_COMPUTE);

private:
  std::string ns_;
  tesseract_collision::CollisionCheckConfig config_;
  StateType state_type_;
};

}  // namespace tesseract_gui::events

#endif  // TESSERACT_QT_COMMON_CONTACT_RESULTS_EVENTS_H
