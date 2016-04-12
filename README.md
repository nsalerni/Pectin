Pectin (CPS840 Project) - [Website](http://www.thecsguy.com/pectin/)
========

This is a sample iOS app that demonstrates multi-party audio/video conferencing using WebRTC and the XirSys cloud infrastructure.

The app allows musicians (no matter where they are geographically located) to collaborate on a song. The app allows up to 3 people to collaborate on a song simulaniously. 

Only the audio of the app is recorded (recording starts and stops with the start/stop of the conference call). 

* Integrates WebRTC using a universal build packaged as a CocoaPod.
* Basic support for camera rotation & audio muting.
* iOS devices support full duplex audio & video using the front camera.

## How the App Works (Technical Explaination)

Firstly, we start by creating an instance of PHConnectionBroker. This class performs a lot of the main app features, incuding discovering peers and negotiating connections with them.

``` obj-c
XSRoom *room = [[XSRoom alloc] initWithAuthToken:nil username:name andRoomName:roomName];
PHConnectionBroker *connectionBroker = [[PHConnectionBroker alloc] initWithDelegate:self];

[connectionBroker addObserver:self forKeyPath:@"peerConnectionState" options:NSKeyValueObservingOptionOld context:NULL];
[connectionBroker connectToRoom:room];
```

Then we wait for the local stream to become ready. Once the local video stream is ready, we can display the video using PHRender. We also add a gesture recognizer so the user can mute/unmute their local audio feed.

``` obj-c
- (void)connectionBroker:(PHConnectionBroker *)broker didAddLocalStream:(RTCMediaStream *)localStream
{
    // Prepare a renderer for the local stream.
    
    self.localRenderer = [self rendererForStream:localStream];
    UIView *theView = self.localRenderer.rendererView;

    UITapGestureRecognizer *tapRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(handleAudioTap:)];
    [theView addGestureRecognizer:tapRecognizer];
}
```

As the peer disovery processes continues, we start to add remote renders for each of them.


``` obj-c
- (void)connectionBroker:(PHConnectionBroker *)broker didAddStream:(RTCMediaStream *)remoteStream
{
    // Prepare a renderer for the remote stream.
    
    id<PHRenderer> remoteRenderer = [self rendererForStream:remoteStream];
    UIView *theView = remoteRenderer.rendererView;

    [self.remoteRenderers addObject:remoteRenderer];

    UITapGestureRecognizer *tapToZoomRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(handleZoomTap:)];
    tapToZoomRecognizer.numberOfTapsRequired = 2;
    [theView addGestureRecognizer:tapToZoomRecognizer];
}

``` 

Once a render receives its first frame, we can safely show it in our view. As the dimensions of the stream change, we have to update the layout.

``` obj-c
- (void)rendererDidReceiveVideoData:(id<PHRenderer>)renderer
{
    if (renderer == self.localRenderer) {
        [self showLocalRenderer];
    }
    
    ...
}

- (void)renderer:(id<PHRenderer>)renderer streamDimensionsDidChange:(CGSize)dimensions
{
    [self.view setNeedsLayout];
}
```

As peers enter and leave the conference call, the remote stream is removed fro the connection broker's set.

``` obj-c
- (void)connectionBroker:(PHConnectionBroker *)broker didRemoveStream:(RTCMediaStream *)remoteStream
{
    [self removeRendererForStream:remoteStream];

    if ([broker.remoteStreams count] == 0) {
        [self showWaitingInterfaceWithDefaultMessage];
    }
}
```

XSPeerClient performs the role of signaling client, establishing a WebSocket connection to the XirSys signaling server. The client exposes a simple API via the XSPeerClientDelegate, and XSRoomObserver protocols.

