#import <UIKit/UIKit.h>

@class MGGooseView;
@class SpringBoard;

typedef NS_ENUM(NSInteger, MGGooseFrameState) {
	MGGooseWillStartDrawing = 0b10000000,
	MGGooseDidFinishDrawing = 0,
	#define e(name, val) MGGooseDidDraw##name = val, MGGooseWillDraw##name = (val | 0b10000000)
	e(Shadow, 1),
	e(Feet, 2),
	e(Body, 3),
	e(Neck, 4),
	e(Eyes, 5),
	e(Beak, 6)
	#undef e
};
typedef void(^MGGooseFrameHandler)(MGGooseView *, MGGooseFrameState);
typedef void(^MGGooseCommonBlock)(MGGooseView *);

@protocol MGMod

@required
@property (nonatomic, assign) BOOL enabled;

@optional
- (void)preferenceWithKey:(NSString *)key didChangeToValue:(id)value;
- (instancetype)initWithGoose:(MGGooseView *)goose;
- (instancetype)initWithGoose:(MGGooseView *)goose bundle:(NSBundle *)bundle;
- (void)handleFrameInState:(MGGooseFrameState)state;
- (void)springboardDidFinishLaunching:(SpringBoard *)application;

@end

// ALL of the methods in this class MUST be called on the main thread.

@interface MGGooseView : UIView
@property (nonatomic, assign) CGFloat facingTo;
@property (nonatomic, assign) BOOL stopsAtEdge;
@property (nonatomic, assign, readonly) CGPoint positionChange;
@property (nonatomic, assign) BOOL autoResetFeet;
- (void)walkForDuration:(NSTimeInterval)duration
	speed:(CGFloat)speed
	completionHandler:(MGGooseCommonBlock)completion;
- (void)setFacingTo:(CGFloat)degress
	animationCompletion:(MGGooseCommonBlock)completion;
- (void)stopWalking;
- (NSUInteger)addFrameHandler:(MGGooseFrameHandler)handler;
- (NSUInteger)addFrameHandlerWithTarget:(id)target action:(SEL)action;
- (void)removeFrameHandlerAtIndex:(NSUInteger)index;
- (BOOL)isFrameAtEdge:(CGRect)frame;
@end