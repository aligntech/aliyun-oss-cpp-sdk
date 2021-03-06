/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <tinyxml.h>

#include "oss_sdk_cpp/utils/utils.h"
#include "oss_sdk_cpp/utils/string_utils.h"
#include "oss_sdk_cpp/utils/xml_utils.h"

#include "oss_sdk_cpp/message/upload_part_copy_result.h"

namespace oss {

const std::string& UploadPartCopyResult::GetLastModified() const {
  return last_modified_;
}

const std::string& UploadPartCopyResult::GetEtag() const {
  return etag_;
}

bool UploadPartCopyResult::DeserializeFromXml(const std::string& content) {
  TiXmlDocument doc;
  if (doc.Parse(content.c_str(), 0, TIXML_ENCODING_UTF8) == NULL)
    return false;

  TiXmlNode* root_node = doc.FirstChild("CopyPartResult");
  if (root_node == NULL)
    return false;

  last_modified_ = GetXmlChildNodeText(root_node, "LastModified");
  std::string str = GetXmlChildNodeText(root_node, "ETag");
  TrimString(str, "\"", &etag_);
  return true;
}

}  // namespace oss
