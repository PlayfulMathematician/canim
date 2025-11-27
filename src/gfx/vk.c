// SPDX-License-Identifier: MIT
#include "canim/core.h"
#include "canim/gfx.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.h>
struct GfxDevice {
  bool headless;
  int width;
  int height;
  VkInstance inst;
  SDL_Window *win;
};

GfxDevice *vk_create_device(CanimResult *result, GfxContainer *container,
                            const GfxInitInfo *info) {
  GfxDevice *dev = calloc(1, sizeof(GfxDevice));
  if (!dev) {
    *result = GFX_DEVICE_CALLOC_ERROR;
    return NULL;
  }

  dev->headless = info->headless;
  dev->width = info->width;
  dev->height = info->height;
  dev->win = NULL;
  if (!info->headless) {
    dev->win = SDL_CreateWindow(
        "Canim Vulkan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        info->width, info->height, SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN);

    if (!dev->win) {
      free(dev);
      *result = SDL_WINDOW_CREATION_ERROR;
      return NULL;
    }
  }
  uint32_t extCount = 0;
  const char **extNames = NULL;

  if (!info->headless) {
    if (!SDL_Vulkan_GetInstanceExtensions(dev->win, &extCount, NULL)) {
      SDL_DestroyWindow(dev->win);
      free(dev);
      *result = 0x03ffffff; /// @todo FIX
      return NULL;
    }

    extNames = malloc(sizeof(char *) * extCount);
    if (!extNames) {
      SDL_DestroyWindow(dev->win);
      free(dev);
      *result = 0x03ffffff; /// @todo FIX

      return NULL;
    }

    SDL_Vulkan_GetInstanceExtensions(dev->win, &extCount, extNames);
  }

  VkApplicationInfo app = {.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                           .pApplicationName = "Canim",
                           .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
                           .pEngineName = "Canim",
                           .engineVersion = VK_MAKE_VERSION(1, 0, 0),
                           .apiVersion = VK_API_VERSION_1_3};

  VkInstanceCreateInfo ci = {.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                             .pApplicationInfo = &app,
                             .enabledLayerCount = 0,
                             .ppEnabledLayerNames = NULL,
                             .enabledExtensionCount = extCount,
                             .ppEnabledExtensionNames = extNames};

  VkResult vkres = vkCreateInstance(&ci, NULL, &dev->inst);

  free(extNames);
  if (vkres != VK_SUCCESS) {
    if (dev->win)
      SDL_DestroyWindow(dev->win);
    free(dev);
    *result = 0x03ffffff; /// @todo FIX

    return NULL;
  }

  *result = SUCCESS;
  return dev;
}
