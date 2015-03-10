#ifndef __PREVIEW_H__
#define __PREVIEW_H__

/// Previews a resource.
class Preview {
	public:
		/// Destructor.
		virtual ~Preview() { };

		/// Render the resource.
		/**
		 * @param width Width of the render context.
		 * @param height Height of the render context.
		 */
		virtual void render(int width, int height) const = 0;
};

#endif