#ifndef _WaveformSelectionProxy_h_
#define _WaveformSelectionProxy_h_

#include <qobject.h>
#include <qcolor.h>
#include <map>
#include <QWave2/qwave2defs.h>
using namespace std;

namespace QWave2 {

class Waveform;
class WaveformRegion;

/// WaveformSelectionProxy manages a region called "selection" on registered waveforms.
/**
   Selection is a region on a waveform that currently has the focus.
   A selection can be created by clicking on a waveform with the left mouse
   button, dragging the mouse and releasing the button.  This mouse motion
   can also be emulated by calling beginSelection, expandSelection and
   freezeSelection methods in the order.  Finally, a selection can also be
   created by calling the select method.

   We call the waveform on which the selection is drawn focused waveform.
   Other waveforms that are registered are called unfocused waveform.

   Slection is drawn as a red rectangle on the focused waveform widget.
   Yellow rectangles with the same span as the selection rectangle are also
   drawn on unfocused waveforms.  We call these yellow rectangles unfocused
   regions.  This color scheme can be changed with the setColorScheme method.

   The focused waveform can be obtained using the getSelectedWaveform method.

   The start time and duration of the selection can be obtained with
   getBeginSeconds and getWidthSeconds methods respectively.
 */
class  WaveformSelectionProxy: public QObject
{
  Q_OBJECT

public:
  WaveformSelectionProxy(QObject* parent=0);
  ~WaveformSelectionProxy();

  /**
     @param wave Waveform to be registered.

     Register the given waveform.
   */
  void registerWaveform(Waveform* wave);
  /**
     @param wave Waveform to be unregistered.

     Unregister the given waveform.
   */
  void unregisterWaveform(Waveform* wave);
  /**
     @param fucused Color of the rectangle of the selection.
     @param unfocused Color of the unfocused regions.

     Change the color scheme of selection and unfocused regions.
   */
  void setColorScheme(const QColor& focused, const QColor& unfocused);
  /**
     @return Begin time of the selection.
   */
  double getBeginSeconds();
  /**
     @return Duration of the selection.
   */
  double getWidthSeconds();
  /**
     @return The pointer to the focused waveform.
   */
  Waveform* getSelectedWaveform();
  /**
     @param beg What will become the start time of the selection.
     @param dur What will become the duration of the selection.
     @param w The waveform to be the focused waveform.

     Create the selection on the given waveform and range.
   */
  void select(const double& beg, const double& dur, Waveform* w);

public slots:
  /**
     @param wave The waveform to be the focused waveform.
     @param beg Where the selection begins.

     Begin the creation of the selection at beg.
   */
  void beginSelection(Waveform* wave, double beg); 
  /**
     @param wave Currently ignored.
     @param beg Where the growing/shrinking edge of the selection is located
     currently.

     Grow and shrink the selection that is being created.
   */
  void expandSelection(Waveform* wave, double beg);
  /**
     @param wave Currently ignored.
     @param beg Where the growing/shrinking edge of the selection is located
     currently.

     Make the right edge of the selection region the pivot edge and place
     the growing/shrinking edge at beg.
   */
  void expandSelectionBegin(Waveform* wave, double beg);
  /**
     @param wave Currently ignored.
     @param beg Where the growing/shrinking edge of the selection is located
     currently.

     Make the left edge of the selection region the pivot edge and place
     the growing/shrinking edge at beg.
   */
  void expandSelectionEnd(Waveform* wave, double beg);
  /**
     @param wave The waveform to be the focused waveform.
     @param beg Where the slection ends.

     Finish the creation of the selection at beg.
   */
  void freezeSelection(Waveform* wave, double beg);

signals:
  /**
     @param beg Begin time of the selection.
     @param dur Duration of the selection.
     @param w Focused waveform.

     This signal is emitted when the the selection is being created and/or
     changed.
   */
  void waveformSelectionChanged(double beg, double dur, Waveform* w);

private slots:
  void waveformDestroyed(QObject* obj=0);

private:
  double _pivot;
  double _beg, _dur;
  bool _flexing;
  QColor _focused;
  QColor _unfocused;
  Waveform* _focusedWaveform;
  map<Waveform*,WaveformRegion*> _reg;
  
};

}

#endif
