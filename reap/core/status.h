/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#ifndef REAP_CORE_UTIL_STATUS_H_
#define REAP_CORE_UTIL_STATUS_H_

#include <memory>
#include <string>

#include "error.h"

namespace reap {

class Status {
 public:
  /// Create a success status.
  Status() {}

  /// \brief Create a status with the specified error code and msg as a
  /// human-readable string containing more detailed information.
  Status(error::Code code, std::string msg);

  /// Copy the specified status.
  Status(const Status& s);
  void operator=(const Status& s);

  static Status OK() { return Status(); }

  /// Returns true iff the status indicates success.
  bool ok() const { return (state_ == NULL); }

  error::Code code() const {
    return ok() ? error::OK : state_->code;
  }

  const std::string& error_message() const {
    return ok() ? empty_string() : state_->msg;
  }

  bool operator==(const Status& x) const {
    return (state_ == x.state_) || (ToString() == x.ToString());
  }
  bool operator!=(const Status& x) const {
    return !(*this == x);
  }

  /// \brief Return a string representation of this status suitable for
  /// printing. Returns the string `"OK"` for success.
  std::string ToString() const;

 private:
  static const std::string& empty_string();
  struct State {
    error::Code code;
    std::string msg;
  };
  // OK status has a `NULL` state_.  Otherwise, `state_` points to
  // a `State` structure containing the error code and message(s)
  std::unique_ptr<State> state_;

  void SlowCopyFrom(const State* src);
};

}  // namespace reap

#endif  // REAP_CORE_UTIL_STATUS_H_
