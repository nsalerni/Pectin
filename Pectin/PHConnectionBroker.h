//
//  PHConnectionManager.h
//  Pectin
//
//  Created by Nick Salerni on 2016-03-01.
//  Copyright © 2016 Nick Salerni. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "XSPeerClient.h"

@class RTCVideoTrack;
@class RTCMediaStream;
@class PHConnectionBroker;
@class PHMediaConfiguration;
@class XSRoom;
@class AFNetworkReachabilityManager;

// Provides information about connected streams, errors and final disconnections.
@protocol PHConnectionBrokerDelegate<NSObject>

- (void)connectionBrokerDidFinish:(PHConnectionBroker *)broker;

- (void)connectionBroker:(PHConnectionBroker *)broker didAddLocalStream:(RTCMediaStream *)localStream;

- (void)connectionBroker:(PHConnectionBroker *)broker didAddStream:(RTCMediaStream *)remoteStream;

- (void)connectionBroker:(PHConnectionBroker *)broker didRemoveStream:(RTCMediaStream *)remoteStream;

- (void)connectionBroker:(PHConnectionBroker *)broker didFailWithError:(NSError *)error;

@end

/**
 *  The connection broker facilitates media streaming.
 *  The broker handles authorization, and signaling to establish and maintain connections.
 */
@interface PHConnectionBroker : NSObject

@property (nonatomic, weak) id<PHConnectionBrokerDelegate> delegate;

@property (nonatomic, strong, readonly) RTCMediaStream *localStream;

@property (nonatomic, strong, readonly) NSArray *remoteStreams;

@property (nonatomic, assign, readonly) XSPeerConnectionState peerConnectionState;

@property (nonatomic, strong, readonly) XSRoom *room;

@property (nonatomic, strong, readonly) AFNetworkReachabilityManager *reachability;

- (instancetype)initWithDelegate:(id<PHConnectionBrokerDelegate>)delegate;

- (BOOL)connectToRoom:(XSRoom *)room withConfiguration:(PHMediaConfiguration *)configuration;

- (void)disconnect;

@end
