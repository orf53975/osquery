/**
 *  Copyright (c) 2014-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed as defined on the LICENSE file found in the
 *  root directory of this source tree.
 */

#include <iostream>

#include <osquery/config/config.h>
#include <osquery/config/parsers/prometheus_targets.h>
#include <osquery/logger.h>
#include <osquery/registry_factory.h>

namespace osquery {

const std::string kPrometheusParserRootKey("prometheus_targets");

std::vector<std::string> PrometheusMetricsConfigParserPlugin::keys() const {
  return {kPrometheusParserRootKey};
}

Status PrometheusMetricsConfigParserPlugin::update(const std::string& source,
                                                   const ParserConfig& config) {
  auto prometheus_targets = config.find(kPrometheusParserRootKey);
  if (prometheus_targets != config.end()) {
    auto obj = data_.getObject();
    data_.copyFrom(prometheus_targets->second.doc(), obj);
    data_.add(kPrometheusParserRootKey, obj);
  }

  return Status();
}

REGISTER_INTERNAL(PrometheusMetricsConfigParserPlugin,
                  "config_parser",
                  "prometheus_targets");
}
