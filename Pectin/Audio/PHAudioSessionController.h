//
//  PHAudioSessionController.h
//  Pectin
//
//  Created by Nick Salerni on 2016-03-01.
//  Copyright © 2016 Nick Salerni. All rights reserved.
//

#import <Foundation/Foundation.h>

@class AVAudioSession;

typedef NS_ENUM(NSUInteger, PHAudioSessionMode)
{
    /**
     *  Ambient playback of sound effects, respecting the ringer setting.
     */
    PHAudioSessionModeAmbient = 0,
    /**
     *  Playback of important sound effects, defeating the ringer and interrupting other apps.
     */
    PHAudioSessionModePlayback = 1,
    /**
     *  Playback and recording of voice audio. Allows use of the iPhone earpiece speaker.
     */
    PHAudioSessionModeVoiceStreaming = 2,
    /**
     *  Playback and recording of voice audio, suitable for use with video.
     */
    PHAudioSessionModeMediaStreaming = 3,
};

@interface PHAudioSessionController : NSObject

@property (nonatomic, assign, readonly) PHAudioSessionMode sessionMode;

@property (nonatomic, assign, readonly, getter = isMediaServerRestarting) BOOL mediaServerRestarting;

@property (nonatomic, assign, readonly, getter = isAudioInterrupted) BOOL audioInterrupted;

- (instancetype)initWithAudioSession:(AVAudioSession *)session;

+ (instancetype)sharedController;

- (NSError *)activateWithAudioMode:(PHAudioSessionMode)sessionMode;

- (NSError *)deactivateSession;

- (NSError *)deactivateSessionWithAudioMode:(PHAudioSessionMode)sessionMode;

@end
