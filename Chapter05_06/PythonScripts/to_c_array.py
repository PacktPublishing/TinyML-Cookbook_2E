def to_c_array(data, c_type, filename, num_cols = 12):

  def to_numpy_dt(dtype):
    if dtype == 'float':
      return 'float32'
    if dtype == 'int32_t':
      return 'int32'
    if dtype == 'uint32_t':
      return 'uint32'
    if dtype == 'int16_t':
      return 'int16'
    if dtype == 'uint16_t':
      return 'uint16'
    if dtype == 'int8_t':
      return 'int8'
    if dtype == 'uint8_t':
      return 'uint8'
    return ''

  str_out = ''

  # Write the header guard
  header_guard = filename.upper()
  str_out += '#ifndef ' + header_guard + '\n'
  str_out += '#define ' + header_guard + '\n'

  # Write the tensor dimensions
  # Scan the dimensions in reverse order
  dim_base = 'const int32_t ' + filename + '_dim'
  for idx, dim in enumerate(data.shape[::-1]):
    str_out += dim_base + str(idx) + ' = '
    str_out += str(dim)
    str_out += ';\n'

  # Reshape the NumPy array and cast the array to desired C data type
  np_type  = to_numpy_dt(c_type)
  data_out = data.flatten()
  data_out = data_out.astype(np_type)

  # Write the tensor total size (Optional)
  size = len(data_out)
  sz_base = 'const int32_t ' + filename + '_sz'
  str_out += sz_base + ' = '
  str_out += str(size) + ';\n'

  # Write the array definition
  str_out += 'const ' + c_type + ' ' + filename + '_data[] = '
  str_out += "\n{\n"

  # Write the values
  for i, val in enumerate(data_out):
    str_out += str(val)

    if (i + 1) < len(data_out):
      str_out += ','
    if (i + 1) % num_cols == 0:
      str_out += '\n'

  str_out += '};\n'
  str_out += '#endif\n'

  # Save the C header file
  h_filename = filename + '.h'
  open(h_filename, "w").write(str_out)