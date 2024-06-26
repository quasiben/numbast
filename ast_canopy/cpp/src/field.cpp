// clang-format off
// SPDX-FileCopyrightText: Copyright (c) 2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0
// clang-format on

#include "ast_canopy.hpp"

#ifndef NDEBUG
#include <iostream>
#endif

namespace ast_canopy {

Field::Field(const clang::FieldDecl *FD, const clang::AccessSpecifier &AS)
    : name(FD->getNameAsString()), type(FD->getType(), FD->getASTContext()) {
  if (AS == clang::AccessSpecifier::AS_public)
    access = access_kind::public_;
  else if (AS == clang::AccessSpecifier::AS_protected)
    access = access_kind::protected_;
  else if (AS == clang::AccessSpecifier::AS_private)
    access = access_kind::private_;
  else {
    // Fields in a class / struct must have an access specifier. See logic
    // in record.cpp.
#ifndef NDEBUG
    std::cout << "Access specifier is NONE for: " << name << std::endl;
#endif
    access = access_kind::public_;
  }
}
} // namespace ast_canopy
