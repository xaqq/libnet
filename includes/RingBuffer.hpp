/*
 * File:   RingBuffer.hpp
 * Author: xaqq
 *
 * Created on May 10, 2012, 4:12 PM
 */

#ifndef RINGBUFFER_HPP
#define	RINGBUFFER_HPP

#include        <memory>
#include        <string>

/**
 * @brief Library namespace
 */
namespace Net
{

  /**
   * @brief Ring buffer class.
   *
   * Its the ring buffer's class used by TcpSocket
   */
  class RingBuffer
  {
    typedef std::auto_ptr<std::string> stringPtr;
  protected:
    /**
     * String object, its the actual buffer.
     */
    stringPtr   _data;
    /**
     * Buffer size (user specified size + 1)
     */
    int         _size;
    /**
     * Start reading offset
     */
    int         _s;
    /**
     * Start writing offset
     */
    int         _e;
    /**
     * Last start offset (used to rollback one read)
     */
    int         _lastStart;
    /**
     * Max size for the buffer to grow if needed.
     * If -1, the buffer can grow indefinitely
     */
    int         _maxSize;

  public:
    /**
     * @brief Constructor.
     *
     * Create a new ring buffer.
     * @param size initial size
     * @param maxSize A value of 0 means the buffer can't grow. It's max size
     * is the same as it's size. A value of -1 means the buffer can grow
     * indefinitely
     */
    RingBuffer(int size, int maxSize = 0);
    /**
     * @brief Destructor
     *
     * Delete the object
     */
    ~RingBuffer();

    /**
     * Read data from the buffer.
     * @param target String where data will be copied
     * @param len Max number of characters to read.
     * @return Number of read characters
     * @throw Does not throw
     */
    int read(std::string &target, int len);

    /**
     * @see read
     * @param target array where data will be copied
     * @param len Max number of characters to read.
     * @return Number of read characters
     * @throw Does not throw
     */
    int read(char *target, int len);

    /**
     * Write data to the buffer.
     * @param source
     * @param len number of bytes to write
     * @return false if write failed, true otherwise
     * @throw Does not throw
     */
    bool write(const char *source, int len);

    /**
     * Rollback the last read.
     * @return true if rollback has an effect, false otherwise
     * @throw Does not throw
     */
    bool readRollback();

    /**
     * Returns the number of readable characters
     * @return Number of bytes readable
     */
    int rAvailable() const ;

    /**
     * Returns the number of characters we can write till the buffer is full.
     * @return Number of bytes writable
     */
    int wAvailable() const ;

  protected:
    void read_(char *target, int len, int &readBytes);
    /**
     * Resize the ring buffer.
     * @note Resizing the buffer is a costly operation. Better allocate a bigger
     *       buffer directly.
     * @param Size to add. Should not be less than 1.
     * @return True if operation was successful. Otherwise false.
     */
    bool resize(int add);


  } ;
}

#endif	/* RINGBUFFER_HPP */

