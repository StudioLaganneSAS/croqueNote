//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "ChordableVectorControlRoot.h"
#include "BarViewVectorControl.h"
#include "PKGridLayout.h"
#include "ChordableWindow.h"
#include "PKVectorEngine.h"
#include "PKStr.h"

//
// ChordableVectorControlRoot
//

ChordableVectorControlRoot::ChordableVectorControlRoot()
{
    this->moving_bar = NULL;

    this->min_x_move_bar = 0;
    this->min_y_move_bar = 0;
    this->max_x_move_bar = 32768;
    this->max_y_move_bar = 32768;

    this->current_bar_col = -1;
    this->current_bar_row = -1;

    this->window = NULL;
	this->grid = NULL;
	this->insertBars = NULL;
    this->eventSent = false;

    this->i_x = 0;
    this->i_y = 0;

    this->showMarker = false;
    this->x_marker   = 0;
    this->y_marker   = 0;
    this->w_marker   = 0;
    this->h_marker   = 0;
}

ChordableVectorControlRoot::~ChordableVectorControlRoot()
{
    
}

void ChordableVectorControlRoot::setWindow(ChordableWindow *window)
{
    this->window = window;
}

void ChordableVectorControlRoot::exportToJPEGFile(std::wstring file, float quality /* 0-1 */)
{
#ifdef MACOSX
	
	PKVectorEngine engine;
	
	CFStringRef path = PKStr::wStringToCFString(file);
	CGContextRef ctx = NULL;
	CFURLRef url;
	CGRect box;
	
	// Determine document width & height
	
	int h = this->getH() - 64;
	double dw = (double) h * 21.0 / 29.7;
	
	int w = (int) dw - 1;
	
	box.origin.x = 0;
	box.origin.y = 0;
	
	box.size.width  = w;
	box.size.height = h;
	
	// Create bitmap context
	
	int size   = 4 * w * h;
	void* data = calloc(size, 1);
	
	CGColorSpaceRef genericColorSpace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
	
	CGContextRef bmCtx = CGBitmapContextCreate(data, w, h, 8,
											   4*w, genericColorSpace, 
											   kCGImageAlphaPremultipliedFirst);
	
	CGContextSetFillColorSpace(bmCtx, genericColorSpace); 
	CGContextSetStrokeColorSpace(bmCtx, genericColorSpace); 
	CGColorSpaceRelease(genericColorSpace);
	
	// Setup context
	
	CGContextTranslateCTM(bmCtx, 
						  -((int)this->getW() - w)/2, 
						  h - 1 + 25); // margin
	
	CGContextScaleCTM(bmCtx, 1.0, -1.0);
	
	// Draw
	
	engine.startWithCGContext(bmCtx);
	engine.setDimensions(w, h);
	this->drawIntoVectorEngine(&engine);
	engine.end();
	
	// Get Image
	
	CGImageRef image = CGBitmapContextCreateImage(bmCtx);
	
	// Export to PNG
	
	url = CFURLCreateWithFileSystemPath(NULL, 
										path,
										kCFURLPOSIXPathStyle,
										false);
	
	CFStringRef type = kUTTypeJPEG;  // public.png
	size_t count = 1; 

	CFStringRef myKeys[1];
	CFTypeRef   myValues[1];
	
	myKeys[0]   = kCGImageDestinationLossyCompressionQuality;
	myValues[0] = (CFTypeRef) CFNumberCreate(NULL, kCFNumberFloatType, &quality);
	
	CFDictionaryRef options = CFDictionaryCreate(NULL, 
												(const void **) myKeys,
												(const void **) myValues, 1,
												&kCFTypeDictionaryKeyCallBacks,
												&kCFTypeDictionaryValueCallBacks);
	
	CGImageDestinationRef dest = CGImageDestinationCreateWithURL(url, type, count, options);
	
	CGImageDestinationAddImage(dest, image, NULL);
	
	CGImageDestinationFinalize(dest);

	CFRelease(options);
	CFRelease(dest);
	
	// Cleanup
	
	CGContextRelease(bmCtx);
	CGImageRelease(image);
	
	CFRelease(url);
	CFRelease(path);
	
#endif	
}

void ChordableVectorControlRoot::exportToPNGFile(std::wstring file)
{
#ifdef MACOSX

	PKVectorEngine engine;
	
	CFStringRef path = PKStr::wStringToCFString(file);
	CGContextRef ctx = NULL;
	CFURLRef url;
	CGRect box;
	
	// Determine document width & height
	
	int h = this->getH() - 64;
	double dw = (double) h * 21.0 / 29.7;
	
	int w = (int) dw - 1;
	
	box.origin.x = 0;
	box.origin.y = 0;
	
	box.size.width  = w;
	box.size.height = h;

	// Create bitmap context
	
	int size   = 4 * w * h;
	void* data = calloc(size, 1);
	
	CGColorSpaceRef genericColorSpace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
	
	CGContextRef bmCtx = CGBitmapContextCreate(data, w, h, 8,
											   4*w, genericColorSpace, 
											   kCGImageAlphaPremultipliedFirst);
	
	CGContextSetFillColorSpace(bmCtx, genericColorSpace); 
	CGContextSetStrokeColorSpace(bmCtx, genericColorSpace); 
	CGColorSpaceRelease(genericColorSpace);
	
	// Setup context
	
	CGContextTranslateCTM(bmCtx, 
						  -((int)this->getW() - w)/2, 
						  h - 1 + 25); // margin
	
	CGContextScaleCTM(bmCtx, 1.0, -1.0);

	// Draw
	
	engine.startWithCGContext(bmCtx);
	engine.setDimensions(w, h);
	this->drawIntoVectorEngine(&engine);
	engine.end();
	
	// Get Image
	
	CGImageRef image = CGBitmapContextCreateImage(bmCtx);
	
	// Export to PNG
	
	url = CFURLCreateWithFileSystemPath(NULL, 
										path,
										kCFURLPOSIXPathStyle,
										false);
	
	CFStringRef type = kUTTypePNG;  // public.png
	size_t count = 1; 
	CFDictionaryRef options = NULL;
	CGImageDestinationRef dest = CGImageDestinationCreateWithURL(url, type, count, options);
	
	CGImageDestinationAddImage(dest, image, NULL);
	
	CGImageDestinationFinalize(dest);
	CFRelease(dest);
	
	// Cleanup
	
	CGContextRelease(bmCtx);
	CGImageRelease(image);
	
	CFRelease(url);
	CFRelease(path);

#endif
}

void ChordableVectorControlRoot::exportToPDFFile(std::wstring file)
{
#ifdef MACOSX

	PKVectorEngine engine;
	
	CFStringRef path = PKStr::wStringToCFString(file);
	CGContextRef ctx = NULL;
	CFURLRef url;
	CGRect box;
	
	// Determine document width & height
	
	int h = this->getH() - 64;
	double dw = (double) h * 21.0 / 29.7;
	
	int w = (int) dw - 1;
	
	box.origin.x = 0;
	box.origin.y = 0;
	
	box.size.width  = w;
	box.size.height = h;
	
	url = CFURLCreateWithFileSystemPath(NULL, 
										path,
										kCFURLPOSIXPathStyle,
										false);
	if(url != NULL) 
	{
		ctx = CGPDFContextCreateWithURL(url,
										&box,
										NULL);
		
		if(ctx != NULL) 
		{
			CFStringRef myKeys[1];
			CFTypeRef myValues[1];
			
			myKeys[0]   = kCGPDFContextMediaBox;
			myValues[0] = (CFTypeRef) CFDataCreate(NULL,(const UInt8 *)&box, sizeof (CGRect));
			
			CFDictionaryRef pageDictionary = CFDictionaryCreate(NULL, 
																(const void **) myKeys,
																(const void **) myValues, 1,
																&kCFTypeDictionaryKeyCallBacks,
																&kCFTypeDictionaryValueCallBacks);
			
			CGPDFContextBeginPage(ctx, pageDictionary);
			
			CGContextTranslateCTM(ctx, 
								  -((int)this->getW() - w)/2, 
								  h - 1 + 25); // margin
			
			CGContextScaleCTM(ctx, 1.0, -1.0);
			
			engine.startWithCGContext(ctx);
			engine.setDimensions(w, h);
			this->drawIntoVectorEngine(&engine);
			engine.end();
			
			CGPDFContextEndPage(ctx);
			CFRelease(pageDictionary);
			CFRelease(myValues[0]);
			
			CGContextRelease(ctx);
		}
		
		CFRelease(url);
	}				
	
	CFRelease(path);

#endif
}

void ChordableVectorControlRoot::drawVectorInternal(PKVectorEngine *engine)
{
    PKVectorControlRoot::drawVectorInternal(engine);

    // Now draw the marker if we need to

    if(this->showMarker)
    {
        PKColor bkgColor = PKColorCreate(210,140,90,255);
        engine->fillRect(this->x_marker, this->y_marker, 
                         this->w_marker, this->h_marker, bkgColor);
    }
}

void ChordableVectorControlRoot::processSafeEvent(std::string  eventName,
					                              void        *payload)
{
    if(eventName == "MOVE_END")
    {
        if(this->window)
        {
            this->window->refreshChordsGrid();
        }
    }

    if(eventName == "INSERT_BARS_SHOW_CONTROL")
    {
		int ww = 75;
		int hh = 58;

        this->insertBars = new InsertBarsVectorControl();

		if(this->insertBars)
		{
			PKVariantInt32 layoutx(1);
			this->insertBars->set(PKControl::LAYOUTX_INT32_PROPERTY, &layoutx);
			PKVariantInt32 layouty(1);
			this->insertBars->set(PKControl::LAYOUTY_INT32_PROPERTY, &layouty);

			PKVariantBool shared(true);
			this->insertBars->set(PKVectorControl::SHARED_VECTOR_ENGINE_BOOL_PROPERTY, &shared);

            PKVariantDouble alpha(0);
            this->insertBars->set(PKVectorControl::ALPHA_DOUBLE_PROPERTY, &alpha);

			this->insertBars->move(this->i_x, this->getY() + this->i_y);
			this->insertBars->resize(ww, hh);
			this->addChild(this->insertBars);

			this->insertBars->build();
			this->insertBars->initialize(this->window);
			this->insertBars->setControlRoot(this);

            // Fade it in

			PKVectorAnimation *anim = new PKVectorAnimation();

            PKVectorAnimationBlock *block1 = new PKVectorAnimationBlock(this->insertBars, 0, 0.2, 
                                             new PKVectorAnimationDescriptorFadeTo(this->insertBars, 1.0));
    	    anim->addAnimationBlock(block1);
			anim->setCompletionHandler(this, "SHOW_INSERT_BARS_CONTROL_ANIMATION", NULL);

			this->queueVectorControlAnimation(anim);
		}
    }
	
	PKVectorControlRoot::processSafeEvent(eventName, payload);
}

void ChordableVectorControlRoot::mouseDown(PKButtonType button,
					                       int x,
					                       int y,
					                       unsigned int mod)
{
    // See if we are hitting a child

	PKControl *child = this->findChildControlAt(x, y);
	
	if(child && (child != this))
	{
        BarViewVectorControl *bar = dynamic_cast<BarViewVectorControl *>(child);

        if(bar != NULL)
        {
            // Check that we aren't in the margin

			int off_x = bar->getX();
			int off_y = bar->getY();

			int w = bar->getW();
			int h = bar->getH();

		    double margin = (double)w/20.0;

			double _x = x - off_x;
			double _y = y - off_y;

			if(_x < margin || _x > w - margin)
			{
                // Do not move the bar if clicked in the margin
                // instead, select the area in between the bars


                PKVectorControlRoot::mouseDown(button, x, y, mod);
                return;
            }

			if(_y < margin || _y > h - margin)
			{
                // Nothing happens in this area
                PKVectorControlRoot::mouseDown(button, x, y, mod);
                return;
            }

            bar->retain();
            this->moving_bar = bar;

            this->mouse_x_original = x;
            this->mouse_y_original = y;

            this->bar_x_original = bar->getX();
            this->bar_y_original = bar->getY();

            this->setTopLevelControl(bar);

            // See how we need to clamp
            PKDialog *topDialog = this->getDialog();

            if(topDialog)
            {
                this->grid = dynamic_cast<PKGridLayout *>(topDialog->findControl("ID_BAR_GRID"));

                if(this->grid)
                {
                    this->grid->relayout();

                    this->min_x_move_bar = this->grid->getX();
                    this->min_y_move_bar = this->grid->getY();
                    this->max_x_move_bar = this->min_x_move_bar + this->grid->getW();
                    this->max_y_move_bar = this->min_y_move_bar + this->grid->getH();

                    this->current_bar_col = this->grid->getColForChild(bar);
                    this->current_bar_row = this->grid->getRowForChild(bar);

                    this->original_bar_col = this->current_bar_col;
                    this->original_bar_row = this->current_bar_row;
                }
            }
        }
    }

    // Call parent
    PKVectorControlRoot::mouseDown(button, x, y, mod);
}

void ChordableVectorControlRoot::mouseUp(PKButtonType button,
					                     int x,
					                     int y,
					                     unsigned int mod)
{
    if(this->moving_bar)
    {
        // See if we need to move the bar
        // to the right spot in the grid layout

        int x_start = this->moving_bar->getX();
        int y_start = this->moving_bar->getY();

        int x_end = this->grid->getXForChildAtPos(this->current_bar_col, this->current_bar_row);
        int y_end = this->grid->getYForChildAtPos(this->current_bar_col, this->current_bar_row);

        if(x_start != x_end || y_start != y_end)
        {
            PKVectorAnimation *move_anim = new PKVectorAnimation();

            PKVectorAnimationBlock *block = new PKVectorAnimationBlock(this->moving_bar, 0.0, 0.2, 
                                            new PKVectorAnimationDescriptorSlide(x_start, y_start, x_end, y_end));
            move_anim->addAnimationBlock(block);
            move_anim->setCompletionHandler(this, "MOVE_END", NULL);

            this->queueVectorControlAnimation(move_anim);
        }

        // Cleanup
        this->moving_bar->release();
        this->moving_bar = NULL;

        this->setTopLevelControl(NULL);
    }

    // Call parent
    PKVectorControlRoot::mouseUp(button, x, y, mod);    
}

void ChordableVectorControlRoot::mouseMove(int x,
					                       int y,
					                       unsigned int mod)
{
    if(this->moving_bar)
    {
        int w = this->moving_bar->getW();
        int h = this->moving_bar->getH();

        // move it
        int d_x = (x - this->mouse_x_original);
        int d_y = (y - this->mouse_y_original);
        
        int new_x = this->bar_x_original + d_x;
        int new_y = this->bar_y_original + d_y;

        // clamp if necessary

        if(new_x < this->min_x_move_bar) new_x = this->min_x_move_bar;
        if(new_y < this->min_y_move_bar) new_y = this->min_y_move_bar;

        if(new_x + w > this->max_x_move_bar) new_x = (this->max_x_move_bar - w);
        if(new_y + h > this->max_y_move_bar) new_y = (this->max_y_move_bar - h);

        // See if we've crossed over a new
        // cell and need to perform layout changes

        int grid_x = (new_x - this->min_x_move_bar) + w/2; // relative to grid layout
        int grid_y = (new_y - this->min_y_move_bar) + h/2; // relative to grid layout

        // Find which rows and cols that is
        // and compare with our current location

        if(this->grid)
        {
            int new_col = this->grid->getColAt(grid_x);
            int new_row = this->grid->getRowAt(grid_y);

            if(new_col != -1 && new_row != 1)
            {
                // See if we've hit another slot in the grid
                if(new_col != this->current_bar_col || new_row != this->current_bar_row)
                {
                    // We need to animate the transition

                    // If we are on the same line, it's much easier:
                    if(new_row == this->current_bar_row)
                    {
                        // We just invert the two elements
                        PKObject *obj = this->grid->getChildAtRowAndCol(new_row, new_col);
                        BarViewVectorControl *new_bar = dynamic_cast<BarViewVectorControl *>(obj);

                        if(new_bar)
                        {
                            PKVectorAnimation *move_anim = new PKVectorAnimation();

                            int x_start = new_bar->getX();
                            int y_start = new_bar->getY();

                            int x_end = this->grid->getXForChildAtPos(this->current_bar_col, this->current_bar_row);
                            int y_end = this->grid->getYForChildAtPos(this->current_bar_col, this->current_bar_row);

                            this->grid->exchangeChildren(new_bar, this->moving_bar);

                            PKVectorAnimationBlock *block = new PKVectorAnimationBlock(new_bar, 0.0, 0.2, 
                                                            new PKVectorAnimationDescriptorSlide(x_start, y_start, x_end, y_end));
                            move_anim->addAnimationBlock(block);

                            this->queueVectorControlAnimation(move_anim);

                            this->current_bar_col = new_col;
                            this->current_bar_row = new_row;
                        }
                    }
                    else // If the rows are different it's more of a puzzle, depending on line breaks
                    {

                    }
                }
            }
        }

        // move & invalidate

        this->moving_bar->move(new_x, new_y);
        this->invalidate();
    }
    else // don't call parent if we are moving a bar
    {
        // Check if we are between bars in order to 
        // draw the insert & paste bar widget...

        bool   redraw = false;
		bool   showIt = false;

        int ww = 75;
		int hh = 58;

        if(this->showMarker)
        {
            redraw = true;
        }

        this->showMarker = false;

		PKControl *child = this->findChildControlAt(x, y);
		
		if(child && (child != this))
		{
			BarViewVectorControl    *bar = dynamic_cast<BarViewVectorControl *>(child);
            InsertBarsVectorControl *ins = dynamic_cast<InsertBarsVectorControl *>(child);

			if(bar != NULL)
			{
				int off_x = bar->getX();
				int off_y = bar->getY();

				int w = bar->getW();
				int h = bar->getH();

				// Check where we are in the bar

			    double margin = (double)w/20.0;

				double _x = x - off_x;
				double _y = y - off_y;

				if(_x <= margin)
				{
					showIt = true;

                    this->i_x = bar->getX() - ww/2;
                    this->i_y = bar->getY() + h - margin/2;

                    if(this->showMarker == false)
                    {
                        this->showMarker = true;
                        this->x_marker = bar->getX() - margin/2;
                        this->y_marker = bar->getY() + margin + margin/2;
                        this->w_marker = margin;
                        this->h_marker = h - 3*margin;
                        this->invalidate();
                    }
				}
				else if(_x >= (w - margin))
				{
					showIt = true;

                    this->i_x = bar->getX() + w - ww/2;
                    this->i_y = bar->getY() + h - margin/2;

                    if(this->showMarker == false)
                    {
                        this->showMarker = true;
                        this->x_marker = bar->getX() + w - margin/2;
                        this->y_marker = bar->getY() + margin + margin/2;
                        this->w_marker = margin;
                        this->h_marker = h - 3*margin;
                        this->invalidate();
                    }
                }
			}

            if(ins != NULL)
            {
                this->showMarker = true;
                showIt = true;
            }
		}

        if(this->showMarker == false && redraw)
        {
            this->invalidate();
        }

		if(!showIt)
		{
            // Cancel event in case it was going to show
            PKSafeEvents::cancelDelayedEventsWithName("INSERT_BARS_SHOW_CONTROL");
            this->eventSent = false;
        }

		if(this->insertBars != NULL)
		{
			// We're showing the insert bars control
			// let's check if we need to hide it

			if(!showIt)
			{
                // Cancel animation if any
                this->cancelAllAnimationsForChild(this->insertBars);

                // Clear input state since we are going
                // to delete the control that is currently
                // under the mouse
                this->clearInputState();

				// Get rid of it

				this->removeChild(this->insertBars);
				this->insertBars->release();
				this->insertBars = NULL;

				this->invalidate();
			}
		}
		else
		{
            // Send a scheduled event to show the control after a delay

            if(showIt && !this->eventSent)
			{
                this->eventSent = true;
                PKSafeEvents::postSafeEventWithDelay(this, 0.35, "INSERT_BARS_SHOW_CONTROL", NULL);
			}
		}


        // Call parent
        PKVectorControlRoot::mouseMove(x, y, mod);        
    }
}
