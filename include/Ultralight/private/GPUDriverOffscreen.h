#pragma once
#include <Ultralight/platform/GPUDriver.h>
#include <memory>
#include <functional>

namespace ultralight {

class GPUDriverOffscreenImpl;

class UExport GPUDriverOffscreen : public GPUDriver {
 public:
  GPUDriverOffscreen();
  virtual ~GPUDriverOffscreen();

  virtual void SetRenderBufferBitmap(uint32_t render_buffer_id,
                                     RefPtr<Bitmap> bitmap);

  virtual bool IsRenderBufferBitmapDirty(uint32_t render_buffer_id);

  virtual void SetRenderBufferBitmapDirty(uint32_t render_buffer_id,
                                          bool dirty);

  // Inherited from GPUDriver
  virtual void BeginSynchronize() override;
  virtual void EndSynchronize() override;
  virtual uint32_t NextTextureId() override;
  virtual void CreateTexture(uint32_t texture_id,
                             Ref<Bitmap> bitmap) override;
  virtual void UpdateTexture(uint32_t texture_id,
                             Ref<Bitmap> bitmap) override;
  virtual void BindTexture(uint8_t texture_unit,
                           uint32_t texture_id) override;
  virtual void DestroyTexture(uint32_t texture_id) override;
  virtual uint32_t NextRenderBufferId() override;
  virtual void CreateRenderBuffer(uint32_t render_buffer_id,
                                  const RenderBuffer& buffer) override;
  virtual void BindRenderBuffer(uint32_t render_buffer_id) override;
  virtual void ClearRenderBuffer(uint32_t render_buffer_id) override;
  virtual void DestroyRenderBuffer(uint32_t render_buffer_id) override;
  virtual uint32_t NextGeometryId() override;
  virtual void CreateGeometry(uint32_t geometry_id,
    const VertexBuffer& vertices,
    const IndexBuffer& indices) override;
  virtual void UpdateGeometry(uint32_t geometry_id,
    const VertexBuffer& vertices,
    const IndexBuffer& indices) override;
  virtual void DrawGeometry(uint32_t geometry_id,
                            uint32_t indices_count,
                            uint32_t indices_offset,
                            const GPUState& state) override;
  virtual void DestroyGeometry(uint32_t geometry_id) override;
  virtual void UpdateCommandList(const CommandList& list) override;
  virtual bool HasCommandsPending() override;
  virtual void DrawCommandList() override;

 protected:
   virtual GPUDriverOffscreenImpl* Impl();

   std::unique_ptr<GPUDriverOffscreenImpl> impl_;
};

}  // namespace ultralight 
