{
  'targets': [
    {
      'target_name': 'noble',
      'conditions': [
        ['OS=="mac"', {
          'dependencies': [
              'lib/mac/binding.gyp:noble_mac',
          ],
        }],
        ['OS=="win"', {
          'dependencies': [
            'lib/winrt/binding.gyp:noble_winrt',
          ],
        }],
      ],
    },
  ],
}
