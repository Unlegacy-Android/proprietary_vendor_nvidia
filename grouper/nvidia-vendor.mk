$(call inherit-product, vendor/nvidia/grouper/nvidia-vendor-blobs.mk)

# Incluide open source libnvos
PRODUCT_PACKAGES += \
	libnvos