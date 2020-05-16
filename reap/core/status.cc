/* Copyright 2020 The REAP Authors. All Rights Reserved. */

#include "status.h"

#include <memory>

namespace reap {

Status::Status(error::Code code, std::string msg) {
  assert(code != error::OK);
  state_ = std::unique_ptr<State>(new State);
  state_->code = code;
  state_->msg = msg;
}

Status::Status(const Status &s)
  : state_((s.state_ == NULL) ? NULL : new State(*s.state_)) {}

void Status::operator=(const Status &s) {
  // The following condition catches both aliasing (when this == &s),
  // and the common case where both s and *this are ok.
  if (state_ != s.state_) {
    SlowCopyFrom(s.state_.get());
  }
}

void Status::SlowCopyFrom(const State* src) {
  if (src == nullptr) {
    state_ = nullptr;
  } else {
    state_ = std::unique_ptr<State>(new State(*src));
  }
}

std::string error_name(error::Code code) {
  return std::to_string(code);
}

std::string Status::ToString() const {
  if (state_ == nullptr) {
    return "OK";
  } else {
    std::string result(error_name(code()));
    result += ": ";
    result += state_->msg;
    return result;
  }
}

const std::string& Status::empty_string() {
  static std::string empty = "";
  return empty;
}

}  // namespace reap
