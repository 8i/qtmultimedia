/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QANDROIDMEDIAPLAYER_H
#define QANDROIDMEDIAPLAYER_H

#include <QObject>
#include <QtCore/private/qjni_p.h>

QT_BEGIN_NAMESPACE

class JMediaPlayer : public QObject
{
    Q_OBJECT
public:
    JMediaPlayer();
    ~JMediaPlayer();

    enum MediaError
    {
        // What
        MEDIA_ERROR_UNKNOWN = 1,
        MEDIA_ERROR_SERVER_DIED = 100,
        MEDIA_ERROR_INVALID_STATE = -38, // Undocumented
        // Extra
        MEDIA_ERROR_IO = -1004,
        MEDIA_ERROR_MALFORMED = -1007,
        MEDIA_ERROR_UNSUPPORTED = -1010,
        MEDIA_ERROR_TIMED_OUT = -110,
        MEDIA_ERROR_NOT_VALID_FOR_PROGRESSIVE_PLAYBACK = 200,
        MEDIA_ERROR_BAD_THINGS_ARE_GOING_TO_HAPPEN = -2147483648 // Undocumented
    };

    enum MediaInfo
    {
        MEDIA_INFO_UNKNOWN = 1,
        MEDIA_INFO_VIDEO_TRACK_LAGGING = 700,
        MEDIA_INFO_VIDEO_RENDERING_START = 3,
        MEDIA_INFO_BUFFERING_START = 701,
        MEDIA_INFO_BUFFERING_END = 702,
        MEDIA_INFO_BAD_INTERLEAVING = 800,
        MEDIA_INFO_NOT_SEEKABLE = 801,
        MEDIA_INFO_METADATA_UPDATE = 802
    };

    enum MediaPlayerState
    {
        Uninitialized = 0x1, /* End */
        Idle = 0x2,
        Preparing = 0x4,
        Prepared = 0x8,
        Initialized = 0x10,
        Started = 0x20,
        Stopped = 0x40,
        Paused = 0x80,
        PlaybackCompleted = 0x100,
        Error = 0x200
    };

    void release();
    void reset();

    int getCurrentPosition();
    int getDuration();
    bool isPlaying();
    int volume();
    bool isMuted();
    jobject display();

    void play();
    void pause();
    void stop();
    void seekTo(qint32 msec);
    void setMuted(bool mute);
    void setDataSource(const QString &path);
    void prepareAsync();
    void setVolume(int volume);
    void setDisplay(jobject surfaceHolder);

    static bool initJNI(JNIEnv *env);

Q_SIGNALS:
    void error(qint32 what, qint32 extra);
    void bufferingChanged(qint32 percent);
    void durationChanged(qint64 duration);
    void progressChanged(qint64 progress);
    void stateChanged(qint32 state);
    void info(qint32 what, qint32 extra);
    void videoSizeChanged(qint32 width, qint32 height);

private:
    QJNIObjectPrivate mMediaPlayer;
};

QT_END_NAMESPACE

#endif // QANDROIDMEDIAPLAYER_H
