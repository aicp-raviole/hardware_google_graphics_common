/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef EXYNOS_PRIMARY_DISPLAY_H
#define EXYNOS_PRIMARY_DISPLAY_H

#include <map>

#include "../libdevice/ExynosDisplay.h"

class ExynosMPPModule;

class ExynosPrimaryDisplay : public ExynosDisplay {
    public:
        /* Methods */
        ExynosPrimaryDisplay(uint32_t type, ExynosDevice *device);
        ~ExynosPrimaryDisplay();
        virtual void setDDIScalerEnable(int width, int height);
        virtual int getDDIScalerMode(int width, int height);
        virtual int32_t SetCurrentPanelGammaSource(const DisplayType type,
                                                   const PanelGammaSource& source) override;
        virtual PanelGammaSource GetCurrentPanelGammaSource() const override {
            return currentPanelGammaSource;
        }

        virtual void initDisplayInterface(uint32_t interfaceType);
    protected:
        /* setPowerMode(int32_t mode)
         * Descriptor: HWC2_FUNCTION_SET_POWER_MODE
         * Parameters:
         *   mode - hwc2_power_mode_t and ext_hwc2_power_mode_t
         *
         * Returns HWC2_ERROR_NONE or the following error:
         *   HWC2_ERROR_UNSUPPORTED when DOZE mode not support
         */
        virtual int32_t setPowerMode(int32_t mode) override;
        virtual bool getHDRException(ExynosLayer* __unused layer);
        virtual int32_t setActiveConfigInternal(hwc2_config_t config, bool force) override;
        virtual int32_t getActiveConfigInternal(hwc2_config_t* outConfig) override;
    public:
        // Prepare multi resolution
        ResolutionInfo mResolutionInfo;

    private:
        static constexpr const char* kDisplayCalFilePath = "/mnt/vendor/persist/display/";
        static constexpr const char* kPanelGammaCalFilePrefix = "gamma_calib_data";
        enum PanelGammaSource currentPanelGammaSource = PanelGammaSource::GAMMA_DEFAULT;

        hwc2_config_t mPendActiveConfig = UINT_MAX;
        bool mFirstPowerOn = true;

        int32_t applyPendingConfig();
        int32_t setPowerOn();
        int32_t setPowerOff();
        int32_t setPowerDoze();
        void firstPowerOn();

        std::string getPanelSysfsPath(const DisplayType& type);
};

#endif
